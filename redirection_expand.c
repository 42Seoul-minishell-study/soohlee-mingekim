/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:44:12 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 20:09:51 by soohlee          ###   ########.fr       */
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
	if (ft_strchr(insert_str, ' '))
		tokens[0][0] = 'e';
	temp = *tokens;
	*tokens = mi_strinsert(temp, insert_str, *start, *offset - 1);
	one_d_free_null(&temp);
	*offset = *start + ft_strlen(insert_str) - 1;
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
	if (!ft_strchr(env_str, '$') || !ft_strncmp(*tokens, "<<", 2))
		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
	one_d_free_null(&env_str);
	return (redir_env_trans(tokens, &start, offset, env));
}

static int	redir_line_expand(char **tokens, char **env)
{
	int		offset;
	//char	*tokens_temp;

	offset = -1;
	while ((*tokens)[++offset])
	{
		if ((*tokens)[offset] == '\'')
			single_quote(tokens, &offset);
		else if ((*tokens)[offset] == '\"')
			double_quote(tokens, &offset, env);
		else if ((*tokens)[offset] == '$')
			redir_env_check(tokens, &offset, env);
	}
	// tokens_temp = *tokens;
	// *tokens = mi_strtrim(tokens_temp, " ");
	// free(tokens_temp);
	// tokens_temp = 0;
	return (0);
}

int	redirection_expand(char ***tokens, char **env)
{	
	int	redir_num;

	redir_num = -1;
	while ((*tokens)[++redir_num])
		redir_line_expand(&((*tokens)[redir_num]), env);
	return (0);
}
