/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:39 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/20 19:14:55 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_pipe_count(char *str)
{
	int	count;

	count = 0;
	str = find_next_pipe(str);
	while (*str != '\0')
	{
		count++;
		str = find_next_pipe(str);
	}
	return (count);
}

static char	***split_tokens(char *str)
{
	char	***ops_and_words;

	str = pass_space(str);
	ops_and_words = malloc(sizeof(char **) * 3);
	if (ops_and_words == NULL)
	{
		perror("malloc");
		exit(1);
	}
	set_ops_and_words(str, ops_and_words);
	ops_and_words[2] = NULL;
	return (ops_and_words);
}

char	****tokenize(char *str)
{
	int		index;
	int		tokens_len;
	char	****tokens;

	add_history(str);
	if (*(pass_space(str)) == '\0')
		return (NULL);
	index = 0;
	tokens_len = get_pipe_count(str) + 1;
	tokens = malloc(sizeof(char ***) * (tokens_len + 1));
	if (tokens == NULL)
		perror_and_exit("malloc", 1);
	tokens[index] = split_tokens(str);
	while (++index < tokens_len)
	{
		str = find_next_pipe(str);
		tokens[index] = split_tokens(str);
		if (tokens[index] == NULL)
			return (free_tokens(&tokens));
	}
	tokens[tokens_len] = NULL;
	if (tokens_check(&tokens) == 0)
		return (NULL);
	return (tokens);
}
