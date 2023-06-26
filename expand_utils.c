/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:34 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/26 17:27:18 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_quote(char **tokens, int *offset)
{
	int		start;
	char	*insert_str;
	char	*temp;

	start = *offset;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\'')
			break ;
	if (!(*tokens)[(*offset)])
	{
		*offset = start;
		return (0);
	}
	insert_str = mi_substr(*tokens, start, (*offset + 1) - start);
	temp = insert_str;
	insert_str = mi_strtrim(temp, "\'");
	one_d_free_null(&temp);
	temp = mi_strinsert(*tokens, insert_str, start, *offset);
	free(*tokens);
	*tokens = temp;
	temp = 0;
	*offset = start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

int	double_quote(char **tokens, int *offset, char **env)
{
	int		start;
	char	*insert_str;
	char	*temp;

	start = *offset;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\"')
			break ;
	if (!(*tokens)[(*offset)])
	{
		*offset = start;
		return (0);
	}
	insert_str = mi_substr(*tokens, start, (*offset + 1) - start);
	temp = insert_str;
	insert_str = mi_strtrim(temp, "\"");
	one_d_free_null(&temp);
	word_expand(&insert_str, env);
	temp = mi_strinsert(*tokens, insert_str, start, *offset);
	free(*tokens);
	*tokens = temp;
	*offset = start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

int	env_trans(char **tokens, int *offset, char **env)
{
	int		start;
	char	*env_str;
	char	*insert_str;
	char	*temp;

	start = *offset;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\''
			|| (*tokens)[(*offset)] == '\"'
				|| (*tokens)[(*offset)] == '$'
					|| (*tokens)[(*offset)] == ' ')
			break ;
	env_str = mi_substr(*tokens, start, *offset - start);
	if (!ft_strchr(env_str, '$'))
		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
	if (env_str[1] == '?')
		insert_str = expand_exit_status(env_str);
	else
		insert_str = get_env(env_str + 1, env);
	if (!insert_str)
		insert_str = mi_strdup("");
	one_d_free_null(&env_str);
	temp = *tokens;
	*tokens = mi_strinsert(temp, insert_str, start, *offset - 1);
	one_d_free_null(&temp);
	*offset = start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

char	*word_expand(char **tokens, char **env)
{
	int	offset;

	offset = -1;
	while ((*tokens)[++offset])
	{
		if ((*tokens)[offset] == '$')
			env_trans(tokens, &offset, env);
	}
	return (0);
}
