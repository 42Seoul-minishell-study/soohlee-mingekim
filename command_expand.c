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

int	cmd_expand(char ***tokens, char **env)
{	
	int	cmd_num;

	cmd_num = -1;
	while ((*tokens)[++cmd_num])
	{
		cmd_line_expand(tokens, &cmd_num, env);
	}
	return (0);
}

int	cmd_line_expand(char ***tokens, int *cmd_num, char **env)
{
	int		offset;

	offset = -1;
	while ((*tokens)[*cmd_num][++offset])
	{
		if ((*tokens)[*cmd_num][offset] == '\'')
			single_quate(&((*tokens)[*cmd_num]), &offset);
		else if ((*tokens)[*cmd_num][offset] == '\"')
			double_quate(&((*tokens)[*cmd_num]), &offset, env);
		else if ((*tokens)[*cmd_num][offset] == '$')
			cmd_env_check(tokens, cmd_num, &offset, env);
	}
	return (0);
}

int	cmd_env_check(char ***tokens, int *cmd_num, int *offset, char **env)
{
	t_retoken	db;
	char		*env_str;

	ft_memset(&db, 0, sizeof(t_retoken));
	db.start = *offset;
	db.offset = offset;
	db.cmd_num = cmd_num;
	while ((*tokens)[*cmd_num][++(*offset)] == '$')
		;
	if ((*offset - db.start) > 1)
		return (0);
	(*offset)--;
	while ((*tokens)[*cmd_num][++(*offset)])
		if ((*tokens)[*cmd_num][(*offset)] == '\''
			|| (*tokens)[*cmd_num][(*offset)] == '\"'
				|| (*tokens)[*cmd_num][(*offset)] == '$'
					|| (*tokens)[*cmd_num][(*offset)] == ' ')
			break ;
	if ((*offset - db.start) == 1)
		return (0);
	env_str = mi_substr((*tokens)[*cmd_num], db.start, *offset - db.start);
	if (!ft_strchr(env_str, '$'))
		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
	one_d_free_null(&env_str);
	return (cmd_env_trans(tokens, &db, env));
}

int	cmd_env_trans(char ***tokens, t_retoken *db, char **env)
{
	char	*insert_str;
	char	*env_str;
	char	*temp;

	env_str = mi_substr((*tokens)[*(db->cmd_num)], \
		db->start, *(db->offset) - db->start);
	if (!env_str)
		exit (1);
	if (!ft_strncmp(env_str + 1, "?", 1))
		insert_str = ft_itoa(g_exit_status);
	else
		insert_str = get_env(env_str + 1, env);
	if (!insert_str)
		insert_str = mi_strdup("");
	one_d_free_null(&env_str);
	if (ft_strchr(insert_str, ' '))
		return (re_tokenize(tokens, *db, insert_str));
	temp = (*tokens)[*(db->cmd_num)];
	(*tokens)[*(db->cmd_num)] = mi_strinsert(temp, insert_str, \
		db->start, *(db->offset) - 1);
	one_d_free_null(&temp);
	*(db->offset) = db->start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}
