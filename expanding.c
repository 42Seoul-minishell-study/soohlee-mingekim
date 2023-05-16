/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:29:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/16 21:49:53 by soohlee          ###   ########.fr       */
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

int	single_quate(char **out_str, int *offset, char **envp)	//하는중;
{
	int		start;
	char	*insert_str;d
	char	*res;
	char	*temp;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\'')
			break ;
	if (!(*out_str)[(*offset)])
		return (0);
	insert_str = ft_substr(*out_str, start, *offset - start);
	temp = insert_str;
	insert_str = ft_strtrim(insert_str, "\'");
	free(temp);
	temp = 0;
	res = ft_strinsert(*out_str, insert_str, start, *offset);
	free(*out_str);
	*out_str = res;
	*offset = start + *offset - start - 2;
	if (envp)
		;
	return (0);
}

int	double_quate(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*insert_str;
	char	*res;
	char	*temp;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\"')
			break ;
	if (!(*out_str)[(*offset)])
		return (0);
	insert_str = ft_substr(*out_str, start, *offset - start);
	temp = insert_str;
	insert_str = word_expanding(insert_str, envp);
	free(temp);
	temp = 0;
	res = ft_strinsert(*out_str, insert_str, start, *offset);
	free(*out_str);
	*out_str = res;
	*offset = start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}

// int	double_quate(char **out_str, int *offset, char **envp)
// {
// 	int		start;
// 	int		end;
// 	char	*double_quate_str;
// 	char	*expanded_str;

// 	start = *offset;
// 	end = *offset;
// 	while ((*out_str)[++end])
// 		if ((*out_str)[end] == '\"')
// 			break ;
// 	if ((*out_str)[end] == '\0')
// 	{
// 		*offset = end - 1;
// 		return (0);
// 	}
// 	double_quate_str = ft_substr(*out_str, start, end - start);	//""포함한 스트링 추출
// 	expanded_str = word_expanding(double_quate_str, envp);	//환경변수 확장
// 	*offset = merge_word(out_str, expanded_str, start, end);
// 	free(expanded_str);
// 	expanded_str = 0;
// 	return (0);
// }
