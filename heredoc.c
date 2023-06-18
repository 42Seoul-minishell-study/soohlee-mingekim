/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:12:51 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 17:31:00 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredocfile(char **filename)
{
	char	*str_num;
	int		i;

	i = 0;
	while (1)
	{
		str_num = ft_itoa(i);
		*filename = ft_strjoin(".heredoc_", str_num);
		free(str_num);
		str_num = 0;
		if (access(*filename, F_OK | R_OK | W_OK) != 0)
			break ;
		free(*filename);
		*filename = 0;
		i++;
	}
	return (0);
}

int	heredoc_excute(char **ops, int redirs_num, char **env)
{
	char	*str;
	int		heredoc_fd;
	char	*filename;
	char	*delimiter;
	int		stdfd[2];

	stdfd[0] = dup(0);
	stdfd[1] = dup(1);
	if (g_exit_status != -2)
		return (0);
	delimiter = ft_strchr(ops[redirs_num], ' ') + 1;
	make_heredocfile(&filename);
	heredoc_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1 && g_exit_status == -2)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		word_expand(&str, env);
		ft_putstr_fd(str, heredoc_fd);
		write(heredoc_fd, "\n", 1);
		free(str);
		str = NULL;
	}
	if (g_exit_status == -3)
	{
		dup2(stdfd[0], 0);
		dup2(stdfd[1], 1);
	}
	close(heredoc_fd);
	free(ops[redirs_num]);
	ops[redirs_num] = ft_strjoin("<< ", filename);
	free(filename);
	filename = NULL;
	return (0);
}

int	find_heredoc(char **ops, char **env)
{
	int		i;

	i = -1;
	while (ops[++i] != NULL)
	{
		if (ft_strncmp(ops[i], "<< ", 3) == 0)
			heredoc_excute(ops, i, env);
		if (g_exit_status == -3)
			break ;
	}
	return (0);
}

int	heredoc(char ****tokens, char **env, int *stdinout_copy)
{
	int	index;
	int	previous_exit_status;

	previous_exit_status = g_exit_status;
	index = -1;
	g_exit_status = -2;
	while (tokens[++index] != NULL)
	{
		find_heredoc(tokens[index][0], env);
		if (g_exit_status == -3)
			break ;
	}
	if (g_exit_status == -3)
	{
		stdinout_copy[CTRL_C_COUNT]++;
		g_exit_status = 1;
		return (0);
	}
	g_exit_status = previous_exit_status;
	return (1);
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
