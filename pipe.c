/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:09:28 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/11 16:01:04 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(char *word, int *flag_out)
{
	if (ft_strncmp(word, "< ", 2) == 0)
	{
		*flag_out = O_RDONLY;
		return (1);
	}
	else if (ft_strncmp(word, "<< ", 3) == 0)
	{
		*flag_out = O_RDONLY;
		return (1);
	}
	*flag_out = 0;
	return (0);
}

int	check_output(char *word, int *flag_out)
{
	if (ft_strncmp(word, "> ", 2) == 0)
	{
		*flag_out = O_WRONLY | O_CREAT;
		return (1);
	}
	else if (ft_strncmp(word, ">> ", 3) == 0)
	{
		*flag_out = O_WRONLY | O_CREAT | O_APPEND;
		return (1);
	}
	*flag_out = 0;
	return (0);
}

int	get_infile_fd(char ***token, int *last_pipe_fd_out)
{
	int		i;
	int		fd;
	int		flag;
	char	*filename;

	i = -1;
	fd = -1;
	while (token[0][++i] != NULL)
	{
		if (check_input(token[0][i], &flag) == 1)
		{
			if (fd != -1)
				close(fd);
			filename = find_next_word(token[0][i]) + 1;
			fd = open(filename, flag);
			if (fd < 0)
			{
				perror(filename);
				return (0);
			}
		}
	}
	if (fd == -1)
		return (1);
	if (*last_pipe_fd_out != -1)
		close(*last_pipe_fd_out);
	*last_pipe_fd_out = fd;
	return (1);
}

int	get_outfile_fd(char ***token, int *pipe_fd_out)
{
	int		i;
	int		fd;
	int		flag;
	char	*filename;

	i = -1;
	fd = -1;
	while (token[0][++i] != NULL)
	{
		if (check_output(token[0][i], &flag) == 1)
		{
			if (fd != -1)
				close(fd);
			filename = find_next_word(token[0][i]) + 1;
			fd = open(filename, flag);
			if (fd < 0)
			{
				perror(filename);
				return (0);
			}
		}
	}
	if (fd == -1)
		return (1);
	close(pipe_fd_out[0]);
	pipe_fd_out[0] = fd;
	return (1);
}

void	exec_command(char ***token, int last_pipe_write_fd, int *fd, char **envp)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		return ;
	else if (cpid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (get_infile_fd(token, &last_pipe_write_fd) == 0)
		exit(1);
	if (get_outfile_fd(token, fd) == 0)
		exit(1);
	if (last_pipe_write_fd != -1)
	{
		if (dup2(last_pipe_write_fd, STDIN_FILENO) < 0)
			perror("dup2");
	}
	if (fd[1] != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
	if (last_pipe_write_fd != -1)
		close(last_pipe_write_fd);
	if (fd[1] != -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	execve(token[1][0], token[1], envp);
	perror("execve");
	exit(1);
}

int	execute(char ****tokens, char **envp)
{
	int		i;
	int		pipe_index;
	int		last_pipe_write_fd;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	last_pipe_write_fd = -1;
	pipe_index = 0;
	while (tokens[pipe_index] != NULL)
		pipe_index++;
	i = 0;
	while (i < pipe_index)
	{
		if (i != pipe_index - 1)
		{
			if (pipe(fd) == -1)
				perror("pipe");
		}
		else
		{
			fd[1] = -1;
			fd[0] = -1;
		}
		if (parsing_cmd_and_options(tokens[i][1], envp) == 0)
		{
			return (0);
		}
		exec_command(tokens[i], last_pipe_write_fd, fd, envp);
		if (last_pipe_write_fd != -1)
			close(last_pipe_write_fd);
		close(fd[1]);
		last_pipe_write_fd = fd[0];
		i++;
	}
	close(fd[0]);
	while (wait(0) > 0)
		;
	return (1);
}
