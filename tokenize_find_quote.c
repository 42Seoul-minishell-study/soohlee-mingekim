/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_find_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:44 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:44 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_next_single_quote(char *str)
{
	char	*temp;

	temp = str++;
	while (*str != '\0' && *str != '\'')
		str++;
	if (*str == '\'')
		return (str);
	if (*str == '\0')
	{
		while (*temp != '\0' && is_space(*temp) == 0   && *temp != '|')
			temp++;
		return (temp);
	}
	return (str);
}

char	*find_next_double_quote(char *str)
{
	char	*temp;

	temp = str++;
	while (*str != '\0' && *str != '\"')
		str++;
	if (*str == '\"')
		return (str);
	if (*str == '\0')
	{
		while (*temp != '\0' && is_space(*temp) == 0  && *temp != '|')
			temp++;
		return (temp);
	}
	return (str);
}
