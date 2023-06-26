/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:43:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 20:24:52 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_only_words(char *str, char ***ops_and_words_out)
{
	int	index_word;

	index_word = 0;
	str = pass_space(str);
	while (*str != '\0' && *str != '|')
	{
		str = split_words(str, &ops_and_words_out[1][index_word]);
		index_word++;
		str = pass_space(str);
	}
	ops_and_words_out[1][index_word] = NULL;
}

static void	re_tokenize(char ***token, char **env)
{
	int		words_count;
	int		ops_count;
	char	*str;

	str = join_all_cmd(token, env);
	printf("str%s\n", str);
	get_ops_and_words_count(str, &ops_count, &words_count);
	free_cmd(token);
	token[1] = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (token[1] == NULL)
		perror_and_exit("malloc", 1);
	split_only_words(str, token);
	free(str);
	words_count = 0;
	while (token[1][words_count] != NULL)
	{
		printf("%d:%s\n", words_count, token[1][words_count]);
		words_count++;
	}
}

void	cmd_expand(char ***token, char **env)
{
	int		index;

	re_tokenize(token, env);
	index = 0;
	while (token[1][index] != NULL)
	{
		line_expand(&(token[1][index]), env, AFTER_TOKENIZE);
		index++;
	}
}
