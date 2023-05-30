/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:51 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:52 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_words(char *str, char **word_out)
{
	int		len;
	char	*temp;

	temp = find_next_word(str);
	len = temp - str;
	*word_out = malloc(sizeof(char) * (len + 1));
	if (*word_out == NULL)
	{
		perror("malloc");
		exit(1);
	}
	ft_memcpy(*word_out, str, len);
	(*word_out)[len] = '\0';
	return (temp);
}
