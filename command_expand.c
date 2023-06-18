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
		cmd_line_expand(tokens, &cmd_num, env);
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
	t_retokendata	db;
	char			*env_str;

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
	env_str = ft_substr((*tokens)[*cmd_num], db.start, *offset - db.start);
	if (!ft_strchr(env_str, '$'))
		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
	one_d_free_null(&env_str);
	return (cmd_env_trans(tokens, &db, env));
}

int	cmd_env_trans(char ***tokens, t_retokendata *db, char **env)
{
	char	*insert_str;
	char	*env_str;
	char	*temp;

	env_str = ft_substr((*tokens)[*(db->cmd_num)], \
		db->start, *(db->offset) - db->start);
	if (!env_str)
		exit (1);
	if (!ft_strncmp(env_str + 1, "?", 1))
		insert_str = ft_itoa(g_exit_status);
	else
		insert_str = get_env(env_str + 1, env);
	if (!insert_str)
		insert_str = ft_strdup("");
	one_d_free_null(&env_str);
	if (ft_strchr(insert_str, ' '))
		return (re_tokenize(tokens, *db, insert_str));
	temp = (*tokens)[*(db->cmd_num)];
	(*tokens)[*(db->cmd_num)] = ft_strinsert(temp, insert_str, \
		db->start, *(db->offset) - 1);
	one_d_free_null(&temp);
	*(db->offset) = db->start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

int	re_tokenize(char ***tokens, t_retokendata db, char *out_insert_str)
{
	char	**insert_twod_array;
	int		len;

	db.tail_space_check = 0;
	db.all_space_check = 0;
	db.front_space_exist = 0;
	db.front_str = ft_substr((*tokens)[*(db.cmd_num)], 0, db.start);
	db.end_str = ft_substr((*tokens)[*(db.cmd_num)], *(db.offset), -1);
	if (out_insert_str[ft_strlen(out_insert_str) - 2] == ' ')
		db.tail_space_check = 1;
	insert_twod_array = ft_split(out_insert_str, ' ');
	if (out_insert_str[0] == ' ')
		db.front_space_exist = 1;
	len = 0;
	while (insert_twod_array[len++])
		;
	insert_two_d_array(tokens, db, insert_twod_array, len);
	two_d_free_null(&insert_twod_array);
	return (2);
}

int	insert_two_d_array(char ***tokens, t_retokendata db, char **insert_twod_array, int twod_len)
{
	char	**new_cmd;
	int		new_cmd_num;
	int		tokens_idx;
	int		insert_idx;

	tokens_idx = 0;
	while ((*tokens)[tokens_idx++])
		;
	new_cmd = (char **)malloc(sizeof(char *) * (tokens_idx + twod_len + 1));
	new_cmd_num = 0;
	tokens_idx = 0;
	insert_idx = 0;
	while (new_cmd_num < *(db.cmd_num))
	{
		new_cmd[new_cmd_num++] = ft_strdup((*tokens)[tokens_idx++]);
	}
	if (((db.front_str)[ft_strlen(db.front_str) - 1] != ' '
		&& db.front_space_exist != 1) || (ft_strlen(db.front_str) == 0))
		new_cmd[new_cmd_num++] = ft_strjoin(db.front_str, insert_twod_array[insert_idx++]);
	else
		new_cmd[new_cmd_num++] = ft_strdup(db.front_str);
	tokens_idx++;
	while (insert_twod_array[insert_idx + 1])
	{
		new_cmd[new_cmd_num++] = ft_strdup(insert_twod_array[insert_idx++]);
		*(db.cmd_num) = *(db.cmd_num) + 1;
	}
	if (db.tail_space_check == 0)
	{
		new_cmd[new_cmd_num++] = ft_strjoin(insert_twod_array[insert_idx], db.end_str);
		*(db.offset) = db.start + ft_strlen(insert_twod_array[insert_idx++]) - 1;
	}
	if (db.tail_space_check == 1)
	{
		new_cmd[new_cmd_num++] = ft_strdup(insert_twod_array[insert_idx]);
		new_cmd[new_cmd_num++] = ft_strdup(db.end_str);
		*(db.offset) = db.start + ft_strlen(insert_twod_array[insert_idx++]) - 1;
	}
	while ((*tokens)[tokens_idx])
	{
		new_cmd[new_cmd_num++] = ft_strdup((*tokens)[tokens_idx++]);
	}
	new_cmd[new_cmd_num] = NULL;
	two_d_free_null(&(*tokens));
	*tokens = new_cmd;
	return (0);
}
