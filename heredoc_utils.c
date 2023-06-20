/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:54:46 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 19:55:10 by soohlee          ###   ########.fr       */
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
