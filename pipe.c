/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:09:28 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/18 18:02:52 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_settings(char ***token, int last_fd, int *fd, char ***envp)
{
	if (get_infile_fd(token, &last_fd) == 0)
		exit(1);
	if (get_outfile_fd(token, fd) == 0)
		exit(1);
	parsing_cmd_and_options(token[1], *envp);
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDIN_FILENO) < 0)
			perror_and_exit("dup2", 1);
	}
	if (fd[1] != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror_and_exit("dup2", 1);
	}
	close_fd(last_fd);
	close_fd(fd[0]);
	close_fd(fd[1]);
}

pid_t	exec_command(char ***token, int last_pipe_fd, int *fd, char ***envp)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		return (cpid);
	else if (cpid < 0)
		perror_and_exit("fork", 1);
	exec_settings(token, last_pipe_fd, fd, envp);
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

static pid_t	pipe_while(char ****tokens, char ***envp, int pipe_count)
{
	int		i;
	int		last_pipe_write_fd;
	int		fd[2];
	pid_t	last_pid;

	i = -1;
	last_pipe_write_fd = -1;
	set_fds_not_use(fd);
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
	return (last_pid);
}

int	pipe_and_cmd(char ****tokens, char ***envp, int pipe_count)
{
	pid_t	last_pid;

	if (pipe_count == 1 && is_builtin(tokens[0][1]) == 1 && \
		tokens[0][0][0] == NULL)
	{
		builtin(tokens[0][1], envp);
		return (1);
	}
	last_pid = pipe_while(tokens, envp, pipe_count);
	while (waitpid(last_pid, &g_exit_status, 0) == 0)
		;
	while (wait(0) > 0)
		;
	set_child_exit_status();
	printf("g_exit %d\n", g_exit_status);
	return (1);
}

int	execute(char *****tokens, char ***envp, int *stdinout_copy)
{
	int		pipe_count;

	pipe_count = 0;
	while ((*tokens)[pipe_count] != NULL)
		pipe_count++;
	if (heredoc(*tokens, *envp, stdinout_copy) == 0)
	{
		heredoc_unlink(*tokens);
		free_tokens(tokens);
		return (0);
	}
	pipe_and_cmd(*tokens, envp, pipe_count);
	heredoc_unlink(*tokens);
	free_tokens(tokens);
	return (1);
}
