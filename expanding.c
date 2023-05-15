/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:29:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/15 17:19:20 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanding(char **out_str, char **envp)
{
	int	offset;

	offset = -1;
	while ((*out_str)[++offset])
	{
		if ((*out_str)[offset] == '\'')
			single_quate(out_str, &offset, envp);
		else if ((*out_str)[offset] == '\"')
			double_quate(out_str, &offset, envp);
	}
	return (0);
}

int	single_quate(char **out_str, int *offset, char **envp)
{
	while ((*out_str)[++(*offset)])
		if ((*out_str)[*offset] == '\'')
			break ;
	if (envp)
		;
	return (0);
}

int	double_quate(char **out_str, int *offset, char **envp)
{
	int		start;
	int		end;
	char	*double_quate_str;
	char	*expanded_str;

	start = *offset;
	end = *offset;
	while ((*out_str)[++end])
		if ((*out_str)[end] == '\"')
			break ;
	if ((*out_str)[end] == '\0')
	{
		*offset = end - 1;
		return (0);
	}
	double_quate_str = ft_substr(*out_str, start, end - start);	//""포함한 스트링 추출
	expanded_str = word_expanding(double_quate_str, envp);	//환경변수 확장
	*offset = merge_word(out_str, expanded_str, start, end);
	free(expanded_str);
	expanded_str = 0;
	return (0);
}
