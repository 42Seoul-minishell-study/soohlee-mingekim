/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:25:31 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 20:24:55 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_quate(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*insert_str;
	char	*res;
	char	*temp;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\'')
			break ;
	if (!(*out_str)[(*offset)])
	{
		*offset = start;
		return (0);
	}
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
	{
		*offset = start;
		return (0);
	}
	insert_str = ft_substr(*out_str, start, (*offset + 1) - start);
	temp = insert_str;
	insert_str = ft_strtrim(temp, "\"");
	free(temp);
	word_expand(&insert_str, envp);
	res = ft_strinsert(*out_str, insert_str, start, *offset);
	free(*out_str);
	*out_str = res;
	*offset = start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}

int	env_trans(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*env_str;
	char	*insert_str;
	char	*res;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\''
			|| (*out_str)[(*offset)] == '\"'
				|| (*out_str)[(*offset)] == '$'
					|| (*out_str)[(*offset)] == ' ')
			break ;
	env_str = ft_substr(*out_str, start, *offset - start);
	if (!ft_strchr(env_str, '$'))
	{
		*offset = *offset - 1;
		free(env_str);
		env_str = 0;
		return (0);
	}
	insert_str = getenv(env_str + 1);
	if (!insert_str)
		insert_str = "";
	free(env_str);
	env_str = 0;
	res = ft_strinsert(*out_str, insert_str, start, *offset - 1);
	free(*out_str);
	*out_str = res;
	*offset = start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}


char	*word_expand(char **out_str, char **envp)
{
	int	offset;

	offset = -1;
	while ((*out_str)[++offset])
	{
		if ((*out_str)[offset] == '$')
			env_trans(out_str, &offset, envp);
	}
	return (0);
}
