/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:39 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:40 by mingekim         ###   ########.fr       */
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

void	print_all_tree(char ****tokens)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (tokens[i] != NULL)
	{
		j = 0;
		while (tokens[i][j] != NULL)
		{
			k = 0;
			while (tokens[i][j][k] != NULL)
			{
				printf("%d %d %d: %s\n", i, j, k, tokens[i][j][k]);
				k++;
			}
			j++;
		}
		i++;
	}
}

char	****tokenize(char *str)
{
	int		index;
	int		tokens_len;
	char	****tokens;

	if (!str)
		return (NULL);
	index = 0;
	tokens_len = get_pipe_count(str) + 1;
	tokens = malloc(sizeof(char ***) * (tokens_len + 1));
	if (tokens == NULL)
		perror_and_exit("malloc", 1);
	tokens[index++] = split_tokens(str);
	while (index < tokens_len)
	{
		str = find_next_pipe(str);
		tokens[index] = split_tokens(str);
		if (tokens[index] == NULL)
			return (free_tokens(&tokens));
		index++;
	}
	tokens[tokens_len] = NULL;
	print_all_tree(tokens);
	return (tokens);
}
