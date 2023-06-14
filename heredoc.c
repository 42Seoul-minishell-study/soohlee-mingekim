/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:12:51 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/02 20:29:46 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_heredoc(char ***redirs, char **env);
int	heredoc_excute(char ***redirs, int redirs_num, char **env);
int	make_heredocfile(char **filename);

int	heredoc(char ****out_data, char **env)
{
	int	process_idx;

	process_idx = -1;
	g_exit_status = -2;
	while (out_data[++process_idx])
	{
		find_heredoc(&(out_data[process_idx][0]), env);
	}
	// g_exit_status = 0;
	return (0);
}

int	find_heredoc(char ***redirs, char **env)
{
	int	i;

	i = -1;
	while ((*redirs)[++i])
	{
		if (ft_strlen((*redirs)[i]) >= 3 && !ft_strncmp((*redirs)[i], "<< ", 3))
			heredoc_excute(redirs, i, env);
	}
	return (0);
}

int	heredoc_excute(char ***redirs, int redirs_num, char **env)
{
	char	*str;
	int		heredoc_fd;
	char	*filename;
	char	*delimiter;

	if (g_exit_status != -2)
		return (0);
	delimiter = ft_strchr((*redirs)[redirs_num], ' ') + 1;
	make_heredocfile(&filename);
	heredoc_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1 && g_exit_status == -2)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1))
		{
			free(str);
			str = 0;
			break ;
		}
		ft_putstr_fd(str, heredoc_fd);
		write(heredoc_fd, "\n", 1);
		free(str);
		str = 0;
	}
	close(heredoc_fd);
	free((*redirs)[redirs_num]);
	(*redirs)[redirs_num] = ft_strjoin("<< ", filename);
	free(filename);
	filename = 0;
	if (env)
		;
	return (0);
}

int	make_heredocfile(char **filename)
{
	char	*str_num;
	int		i;

	i = 0;
	while (1)
	{
		str_num = ft_itoa(i);
		*filename = ft_strjoin(".heredoc_", str_num);
		if (access(*filename, F_OK | R_OK | W_OK) != 0)
			break ;
		free(str_num);
		str_num = 0;
		free(*filename);
		*filename = 0;
		i++;
	}
	return (0);
}

int	heredoc_unlink(char ****tokens)
{
	int	process_idx;
	int	redir_idx;

	process_idx = -1;
	while (tokens[++process_idx])
	{
		redir_idx = -1;
		while (tokens[process_idx][0][++redir_idx])
		{
			if (!ft_strncmp(tokens[process_idx][0][redir_idx], "<< ", 3))
			{
				unlink(ft_strchr(tokens[process_idx][0][redir_idx], ' ') + 1);
			}
		}
	}
	return (0);
}
