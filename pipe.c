/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:09:28 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:11 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(char ***token, int last_pipe_write_fd, int *fd, char **envp)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		return ;
	else if (cpid < 0)
		perror_and_exit("fork", 1);
	if (get_infile_fd(token, &last_pipe_write_fd) == 0)
		exit(1);
	if (get_outfile_fd(token, fd) == 0)
		exit(1);
	if (last_pipe_write_fd != -1 && dup2(last_pipe_write_fd, STDIN_FILENO) < 0)
		perror_and_exit("dup2", 1);
	if (fd[1] != -1 && dup2(fd[1], STDOUT_FILENO) < 0)
		perror_and_exit("dup2", 1);
	close_fd(last_pipe_write_fd);
	close_fd(fd[0]);
	close_fd(fd[1]);
	execve(token[1][0], token[1], envp);
	perror_and_exit("execve", 1);
}

int	pipe_and_cmd(char ****tokens, char **envp, int pipe_count)
{
	int		i;
	int		last_pipe_write_fd;
	int		fd[2];

	set_fds_not_use(fd);
	last_pipe_write_fd = -1;
	i = -1;
	while (++i < pipe_count)
	{
		if (i != pipe_count - 1)
		{
			if (pipe(fd) == -1)
				perror_and_exit("pipe", 1);
		}
		else
			set_fds_not_use(fd);
		if (parsing_cmd_and_options(tokens[i][1], envp) == 0)
			return (0);
		exec_command(tokens[i], last_pipe_write_fd, fd, envp);
		close_fd(last_pipe_write_fd);
		close(fd[1]);
		last_pipe_write_fd = fd[0];
	}
	close(fd[0]);
	while (wait(0) > 0)
		;
	return (1);
}

int	execute(char ****tokens, char **envp)
{
	int		pipe_count;

	pipe_count = 0;
	while (tokens[pipe_count] != NULL)
		pipe_count++;
	//here_doc
	if (pipe_and_cmd(tokens, envp, pipe_count) == 0)
	{
		return (0);
	}
	return (1);
}
