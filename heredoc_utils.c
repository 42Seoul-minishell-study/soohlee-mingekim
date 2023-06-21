/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:54:46 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/21 11:01:38 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	make_heredocfile(char **filename)
{
	char	*str_num;
	int		i;

	i = 0;
	while (1)
	{
		str_num = ft_itoa(i);
		*filename = mi_strjoin(".heredoc_", str_num);
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