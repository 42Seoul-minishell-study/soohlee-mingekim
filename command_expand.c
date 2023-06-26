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
	split_ops_and_words(str, token);
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

	//if (!is_expand_needed(token[1]))
	//	return ;
	re_tokenize(token, env);
	index = 0;
	while (token[1][index] != NULL)
	{
		in_quote_expand(&(token[1][index]), env);
		index++;
	}
}
