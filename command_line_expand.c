/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:34:29 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/26 15:34:31 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_env_trans(char **tokens, int *start, int *offset, char **env)
{
	char	*insert_str;
	char	*temp;
	char	*env_str;

	env_str = mi_substr(*tokens, *start, *offset - *start);
	if (!env_str)
		exit (1);
	insert_str = get_env(env_str + 1, env);
	if (!insert_str)
		insert_str = mi_strdup("");
	one_d_free_null(&env_str);
	temp = insert_str;
	insert_str = mi_strtrim(temp, " ");
	one_d_free_null(&temp);
	temp = *tokens;
	*tokens = mi_strinsert(temp, insert_str, *start, *offset - 1);
	one_d_free_null(&temp);
	*offset = *start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

static int	single_quote_expand(char **tokens, int *offset)
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

static int	double_quote_expand(char **tokens, int *offset, char **env)
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

static int	redir_env_check(char **tokens, int *offset, char **env)
{
	int		start;
	char	*env_str;

	start = *offset;
	while ((*tokens)[++(*offset)] == '$')
		;
	if ((*offset - start) > 1)
		return (0);
	(*offset)--;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\''
			|| (*tokens)[(*offset)] == '\"'
				|| (*tokens)[(*offset)] == '$'
					|| (*tokens)[(*offset)] == ' ')
			break ;
	if ((*offset - start) == 1)
		return (0);
	env_str = mi_substr(*tokens, start, *offset - start);
	if (!ft_strchr(env_str, '$'))
		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
	one_d_free_null(&env_str);
	return (redir_env_trans(tokens, &start, offset, env));
}

void	line_expand(char **cmd, char **env, int flag)
{
	int		offset;
	char	*tokens_temp;

	offset = -1;
	while ((*cmd)[++offset])
	{
		if ((*cmd)[offset] == '\'' && flag == AFTER_TOKENIZE)
			single_quote_expand(cmd, &offset);
		else if ((*cmd)[offset] == '\"' && flag == AFTER_TOKENIZE)
			double_quote_expand(cmd, &offset, env);
		else if ((*cmd)[offset] == '\'' && flag == BEFORE_TOKENIZE)
			skip_single_quote(cmd, &offset);
		else if ((*cmd)[offset] == '\"' && flag == BEFORE_TOKENIZE)
			skip_double_quote(cmd, &offset);
		else if ((*cmd)[offset] == '$' && flag == BEFORE_TOKENIZE)
			redir_env_check(cmd, &offset, env);
	}
	tokens_temp = *cmd;
	*cmd = mi_strtrim(tokens_temp, " ");
	free(tokens_temp);
	tokens_temp = 0;
}
