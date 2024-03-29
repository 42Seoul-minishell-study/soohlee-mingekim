/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:12:51 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/21 17:51:26 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_readline(char *delimiter, int heredoc_fd, char **env)
{
	char	*str;

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
	return (0);
}

static void	dup_perror(int *stdfd)
{
	if (stdfd[0] < 0)
		perror_and_exit("dup", 1);
	if (stdfd[1] < 0)
		perror_and_exit("dup", 1);
}

static int	heredoc_excute(char **ops, int redirs_num, char **env)
{
	int		heredoc_fd;
	char	*filename;
	char	*delimiter;
	int		stdfd[2];

	stdfd[0] = dup(0);
	stdfd[1] = dup(1);
	dup_perror(stdfd);
	if (g_exit_status != -2)
		return (0);
	delimiter = ft_strchr(ops[redirs_num], ' ') + 1;
	make_heredocfile(&filename);
	heredoc_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc_readline(delimiter, heredoc_fd, env);
	if (g_exit_status == -3)
	{
		if (dup2(stdfd[0], 0) < 0)
			perror_and_exit("dup2", 1);
		if (dup2(stdfd[1], 1) < 0)
			perror_and_exit("dup2", 1);
	}
	close(heredoc_fd);
	free(ops[redirs_num]);
	ops[redirs_num] = mi_strjoin("<< ", filename);
	return (one_d_free_null(&filename));
}

static int	find_heredoc(char **ops, char **env)
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
	g_exit_status = 0;
	return (1);
}
