/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_get_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:27 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/14 17:06:04 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_open(char *str, int flag)
{
	int		fd;
	char	*file_name;

	file_name = find_next_word(str) + 1;
	fd = open(file_name, flag);
	if (fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	return (fd);
}

static int	file_write_open(char *str, int flag)
{
	int		fd;
	char	*file_name;

	file_name = find_next_word(str) + 1;
	fd = open(file_name, flag, 0644);
	if (fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	return (fd);
}

int	get_infile_fd(char ***token, int *last_pipe_fd_out)
{
	int		i;
	int		fd;
	int		flag;

	i = -1;
	fd = -1;
	while (token[0][++i] != NULL)
	{
		if (check_input(token[0][i], &flag) == 1)
		{
			if (fd != -1)
				close(fd);
			fd = file_open(token[0][i], flag);
			if (fd < 0)
				return (0);
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

	i = -1;
	fd = -1;
	while (token[0][++i] != NULL)
	{
		if (check_output(token[0][i], &flag) == 1)
		{
			if (fd != -1)
				close(fd);
			fd = file_write_open(token[0][i], flag);
			if (fd < 0)
				return (0);
		}
	}
	if (fd == -1)
		return (1);
	if (pipe_fd_out[1] != -1)
		close(pipe_fd_out[1]);
	pipe_fd_out[1] = fd;
	return (1);
}
