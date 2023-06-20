/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:41 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/20 20:32:12 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_check(char ***token)
{
	if (token[1][0] == NULL && token[0][0] == NULL)
		return (0);
	return (1);
}

static int	operation_check(char ***token)
{
	int		i;
	char	*temp;

	i = 0;
	while (token[0][i] != NULL)
	{
		temp = find_next_word(token[0][i]);
		temp++;
		if (*temp == '<' || *temp == '>' || *temp == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	tokens_check(char *****tokens)
{
	int		index;

	index = 0;
	while ((*tokens)[index] != NULL)
	{
		if (pipe_check((*tokens)[index]) == 0)
		{
			free_tokens(tokens);
			write(2, "syntax error\n", 14);
			g_exit_status = 258;
			return (0);
		}
		if (operation_check((*tokens)[index]) == 0)
		{
			free_tokens(tokens);
			write(2, "syntax error\n", 14);
			g_exit_status = 258;
			return (0);
		}
		index++;
	}
	return (1);
}
