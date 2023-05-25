/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:43:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/23 02:10:57 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_expand(char ***out_cmd, char **envp)
{	
	int	cmd_num;

	cmd_num = -1;
	while ((*out_cmd)[++cmd_num])
		cmd_line_expand(out_cmd, &cmd_num, envp);
	if (envp)
		;
	return (0);
}

int	cmd_line_expand(char ***out_cmd, int *cmd_num, char **envp)
{
	int		offset;

	offset = -1;
	while ((*out_cmd)[*cmd_num][++offset])
	{
		if ((*out_cmd)[*cmd_num][offset] == '\'')
			single_quate(&((*out_cmd)[*cmd_num]), &offset, envp);
		else if ((*out_cmd)[*cmd_num][offset] == '\"')
			double_quate(&((*out_cmd)[*cmd_num]), &offset, envp);
		else if ((*out_cmd)[*cmd_num][offset] == '$')
			cmd_env_trans(out_cmd, cmd_num, &offset, envp);
	}
	return (0);
}

int	cmd_env_trans(char ***out_cmd, int *cmd_num, int *offset, char **envp)
{
	t_retokendata db;
	char	*env_str;
	char	*insert_str;
	char	*res;

	db.start = *offset;
	db.offset = offset;
	db.cmd_num = cmd_num;
	while ((*out_cmd)[*cmd_num][++(*offset)] == '$')
		;
	if ((*offset - db.start) > 1)
		return (0);
	(*offset)--;
	while ((*out_cmd)[*cmd_num][++(*offset)])
		if ((*out_cmd)[*cmd_num][(*offset)] == '\''
			|| (*out_cmd)[*cmd_num][(*offset)] == '\"'
				|| (*out_cmd)[*cmd_num][(*offset)] == '$'
					|| (*out_cmd)[*cmd_num][(*offset)] == ' ')
			break ;
	if ((*offset - db.start) == 1)
		return (0);
	env_str = ft_substr((*out_cmd)[*cmd_num], db.start, *offset - db.start);
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
	if (ft_strchr(insert_str, ' '))
	{
		free(env_str);
		env_str = 0;
		re_tokenize(out_cmd, db, insert_str);
		return (2);
	}
	free(env_str);
	env_str = 0;
	res = ft_strinsert((*out_cmd)[*cmd_num], insert_str, db.start, *offset - 1);
	free((*out_cmd)[*cmd_num]);
	(*out_cmd)[*cmd_num] = res;
	*offset = db.start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}

int	re_tokenize(char ***out_cmd, t_retokendata db, char *out_insert_str)
{
	char	**insert_twod_array;
	int		len;

	db.front_space_exist = 0;
	db.front_str = ft_substr((*out_cmd)[*(db.cmd_num)], 0, db.start);
	db.end_str = ft_substr((*out_cmd)[*(db.cmd_num)], *(db.offset), -1);
	insert_twod_array = ft_split(out_insert_str, ' ');
	if (out_insert_str[0] == ' ')
		db.front_space_exist = 1;
	len = 0;
	while (insert_twod_array[len++])
		;
	insert_two_d_array(out_cmd, db, insert_twod_array, len);
	two_d_free(insert_twod_array);
	insert_twod_array = 0;
	return (0);
}

int	insert_two_d_array(char ***out_cmd, t_retokendata db, char **insert_twod_array, int twod_len)
{
	char	**new_cmd;
	int		new_cmd_num;
	int		out_cmd_idx;
	int		insert_idx;

	out_cmd_idx = 0;
	while ((*out_cmd)[out_cmd_idx++])
		;
	new_cmd = (char **)malloc(sizeof(char *) * (out_cmd_idx + twod_len + 1));
	new_cmd_num = 0;
	out_cmd_idx = 0;
	insert_idx = 0;
	while (new_cmd_num < *(db.cmd_num))
	{
		new_cmd[new_cmd_num++] = ft_strdup((*out_cmd)[out_cmd_idx++]);
	}
	if ((db.front_str)[ft_strlen(db.front_str) - 1] != ' '
		&& db.front_space_exist != 1)
		new_cmd[new_cmd_num++] = ft_strjoin(db.front_str, insert_twod_array[insert_idx++]);
	else
		new_cmd[new_cmd_num++] = ft_strdup(db.front_str);
	out_cmd_idx++;
	while (insert_twod_array[insert_idx + 1])
	{
		new_cmd[new_cmd_num++] = ft_strdup(insert_twod_array[insert_idx++]);
		*(db.cmd_num) = *(db.cmd_num) + 1;
	}
	new_cmd[new_cmd_num++] = ft_strjoin(insert_twod_array[insert_idx], db.end_str);
	*(db.offset) = db.start + ft_strlen(insert_twod_array[insert_idx++]) - 1;
	while ((*out_cmd)[out_cmd_idx])
	{
		new_cmd[new_cmd_num++] = ft_strdup((*out_cmd)[out_cmd_idx++]);
	}
	new_cmd[new_cmd_num] = NULL;
	two_d_free(*out_cmd);
	*out_cmd = new_cmd;
	return (0);
}
