/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_ops_and_words.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:47 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:48 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*skip_spaces_and_words(char *str, int redir_index, int *count_out)
{
	str += redir_index;
	str = pass_space(str);
	str = find_next_word(str);
	(*count_out)++;
	return (str);
}
void	get_ops_and_words_count(char *str, \
									int *ops_count_out, int *words_count_out)
{
	*ops_count_out = 0;
	*words_count_out = 0;
	while (*str != '\0' && *str != '|')
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			str = skip_spaces_and_words(str, 2, ops_count_out);
		else if (ft_strncmp(str, "<", 1) == 0)
			str = skip_spaces_and_words(str, 1, ops_count_out);
		else if (ft_strncmp(str, ">>", 2) == 0)
			str = skip_spaces_and_words(str, 2, ops_count_out);
		else if (ft_strncmp(str, ">", 1) == 0)
			str = skip_spaces_and_words(str, 1, ops_count_out);
		else
			str = skip_spaces_and_words(str, 0, words_count_out);
		str = pass_space(str);
	}
}

void	split_ops_and_words(char *str, char ***ops_and_words_out)
{
	int	index_op;
	int	index_word;

	index_op = 0;
	index_word = 0;
	str = pass_space(str);
	while (*str != '\0' && *str != '|')
	{
		if (is_redirection(str) == 1)
		{
			str = split_ops(str, &ops_and_words_out[0][index_op]);
			index_op++;
		}
		else
		{
			str = split_words(str, &ops_and_words_out[1][index_word]);
			index_word++;
		}
		str = pass_space(str);
	}
	ops_and_words_out[0][index_op] = NULL;
	ops_and_words_out[1][index_word] = NULL;
}

char	**set_ops_and_words(char *str, char ***ops_and_words_out)
{
	int	words_count;
	int	ops_count;

	get_ops_and_words_count(str, &ops_count, &words_count);
	ops_and_words_out[0] = malloc(sizeof(char *) * (ops_count + 1));
	if (ops_and_words_out[0] == NULL)
	{
		perror("malloc");
		exit(1);
	}
	ops_and_words_out[1] = malloc(sizeof(char *) * (words_count + 1));
	if (ops_and_words_out[1] == NULL)
	{
		perror("malloc");
		free(ops_and_words_out[0]);
		exit(1);
	}
	split_ops_and_words(str, ops_and_words_out);
	return (NULL);
}
