/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:09:28 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/17 18:57:23 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin(char **cmd, char ***env)
{
	if (cmd[0] == NULL)
		return ;
	if (ft_strlen(cmd[0]) == 2 && !ft_strncmp(cmd[0], "cd", 3))
		ft_cd(cmd, env);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd();
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "env", 4))
		ft_env(*env);
	else if (ft_strlen(cmd[0]) == 6 && !ft_strncmp(cmd[0], "export", 7))
		ft_export(cmd, env);
	else if (ft_strlen(cmd[0]) == 5 && !ft_strncmp(cmd[0], "unset", 6))
		ft_unset(cmd, env);
}

int	is_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (ft_strlen(cmd[0]) == 2 && !ft_strncmp(cmd[0], "cd", 3))
		return (1);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "pwd", 4))
		return (1);
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "echo", 5))
		return (1);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "env", 4))
		return (1);
	else if (ft_strlen(cmd[0]) == 6 && !ft_strncmp(cmd[0], "export", 7))
		return (1);
	else if (ft_strlen(cmd[0]) == 5 && !ft_strncmp(cmd[0], "unset", 6))
		return (1);
	return (0);
}

pid_t	exec_command(char ***token, int last_pipe_write_fd, int *fd, char ***envp)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		return (cpid);
	else if (cpid < 0)
		perror_and_exit("fork", 1);
	if (get_infile_fd(token, &last_pipe_write_fd) == 0)
		exit(1);
	if (get_outfile_fd(token, fd) == 0)
		exit(1);
	parsing_cmd_and_options(token[1], *envp);
	if (last_pipe_write_fd != -1 && dup2(last_pipe_write_fd, STDIN_FILENO) < 0)
		perror_and_exit("dup2", 1);
	if (fd[1] != -1 && dup2(fd[1], STDOUT_FILENO) < 0)
		perror_and_exit("dup2", 1);
	close_fd(last_pipe_write_fd);
	close_fd(fd[0]);
	close_fd(fd[1]);
	if (is_builtin(token[1]) == 1)
	{
		builtin(token[1], envp);
		exit(g_exit_status);
	}
	else
	{
		execve(token[1][0], token[1], *envp);
		perror_and_exit("execve", 1);
	}
	return (-1);
}

int	pipe_and_cmd(char ****tokens, char ***envp, int pipe_count)
{
	int		i;
	int		last_pipe_write_fd;
	pid_t	last_pid;
	int		fd[2];

	set_fds_not_use(fd);
	last_pipe_write_fd = -1;
	i = -1;
	if (pipe_count == 1 && is_builtin(tokens[0][1]) == 1 && tokens[0][0][0] == NULL)
	{
		builtin(tokens[0][1], envp);
		return (1);
	}
	while (++i < pipe_count)
	{
		if (i != pipe_count - 1)
		{
			if (pipe(fd) == -1)
				perror_and_exit("pipe", 1);
		}
		else
			fd[1] = -1;
		last_pid = exec_command(tokens[i], last_pipe_write_fd, fd, envp);
		close_fd(last_pipe_write_fd);
		close(fd[1]);
		last_pipe_write_fd = fd[0];
	}
	close(fd[0]);
	while (waitpid(last_pid, &g_exit_status, 0) == 0)
		;
	while (wait(0) > 0)
		;
	printf("g_exit %d\n", WEXITSTATUS(g_exit_status));
	return (1);
}

int	execute(char ****tokens, char ***envp, int *stdinout_copy)
{
	int		pipe_count;

	pipe_count = 0;
	while (tokens[pipe_count] != NULL)
		pipe_count++;
	if (heredoc(tokens, *envp, stdinout_copy) == 0)
		return (0);
	if (pipe_and_cmd(tokens, envp, pipe_count) == 0)
		return (0);
	heredoc_unlink(tokens);
	return (1);
}
