/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:49 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:50 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_next_pipe(char *str)
{
	while (*str != '\0' && *str != '|')
	{
		if (ft_strncmp(str, "\'", 1) == 0)
		{
			str = find_next_single_quote(str);
		}
		else if (ft_strncmp(str, "\"", 1) == 0)
		{
			str = find_next_double_quote(str);
		}
		str++;
	}
	if (*str == '|')
		str++;
	return (str);
}

char	*find_next_word(char *str)
{
	while (*str != '\0' && *str != ' ' && *str != '|')
	{
		if (*str == '\'')
		{
			str = find_next_single_quote(str);
			return (++str);
		}
		else if (*str == '\"')
		{
			str = find_next_double_quote(str);
			return (++str);
		}
		str++;
	}
	return (str);
}

char	*pass_space(char *str)
{
	while (*str != '\0' && *str == ' ' && *str != '|')
	{
		str++;
	}
	return (str);
}

int	is_redirection(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	return (0);
}

char	****free_tokens(char *****tokens)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while ((*tokens)[i] != NULL)
	{
		j = 0;
		while ((*tokens)[i][j] != NULL)
		{
			k = 0;
			while ((*tokens)[i][j][k] != NULL)
				free((*tokens)[i][j][k++]);
			free((*tokens)[i][j++]);
		}
		free((*tokens)[i++]);
	}
	free(*tokens);
	*tokens = NULL;
	return (NULL);
}
