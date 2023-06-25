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

// static int	mi_isalnum(int c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	else if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }

// static int	cmd_env_trans(char ***tokens, t_retoken *db, char **env)
// {
// 	char	*insert_str;
// 	char	*env_str;
// 	char	*temp;

// 	env_str = mi_substr((*tokens)[*(db->cmd_num)], \
// 		db->start, *(db->offset) - db->start);
// 	if (!ft_strncmp(env_str + 1, "?", 1))
// 		insert_str = ft_itoa(g_exit_status);
// 	else
// 		insert_str = get_env(env_str + 1, env);
// 	one_d_free_null(&env_str);
// 	if (!insert_str)
// 		insert_str = mi_strdup("");
// 	if (ft_strchr(insert_str, ' '))
// 		return (re_tokenize(tokens, *db, insert_str) + \
// 			one_d_free_null(&insert_str));
// 	temp = (*tokens)[*(db->cmd_num)];
// 	(*tokens)[*(db->cmd_num)] = mi_strinsert(temp, insert_str, \
// 		db->start, *(db->offset) - 1);
// 	one_d_free_null(&temp);
// 	*(db->offset) = db->start + ft_strlen(insert_str) - 1;
// 	one_d_free_null(&insert_str);
// 	return (0);
// }

// static int	cmd_env_check(char ***tokens, int *cmd_num, int *offset, char **env)
// {
// 	t_retoken	db;
// 	char		*env_str;

// 	ft_memset(&db, 0, sizeof(t_retoken));
// 	db.start = *offset;
// 	db.offset = offset;
// 	db.cmd_num = cmd_num;
// 	while ((*tokens)[*cmd_num][++(*offset)] == '$')
// 		;
// 	if ((*offset - db.start) > 1)
// 		return (0);
// 	(*offset)--;
// 	while ((*tokens)[*cmd_num][++(*offset)])
// 		if (!mi_isalnum((*tokens)[*cmd_num][(*offset)]))
// 			break ;
// 	if ((*offset - db.start) == 1 && ((*tokens)[*cmd_num][(*offset)] != '?'))
// 		return (0);
// 	if ((*tokens)[*cmd_num][(*offset)] == '?')
// 		(*offset)++;
// 	db.last_flag = (*tokens)[*cmd_num + 1] == NULL;
// 	env_str = mi_substr((*tokens)[*cmd_num], db.start, *offset - db.start);
// 	if (!ft_strchr(env_str, '$'))
// 		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
// 	one_d_free_null(&env_str);
// 	return (cmd_env_trans(tokens, &db, env));
// }

// static int	cmd_line_expand(char ***tokens, int *cmd_num, char **env)
// {
// 	int		offset;

// 	offset = -1;
// 	while ((*tokens)[*cmd_num][++offset])
// 	{
// 		if ((*tokens)[*cmd_num][offset] == '\'')
// 			single_quate(&((*tokens)[*cmd_num]), &offset);
// 		else if ((*tokens)[*cmd_num][offset] == '\"')
// 			double_quate(&((*tokens)[*cmd_num]), &offset, env);
// 		else if ((*tokens)[*cmd_num][offset] == '$')
// 			cmd_env_check(tokens, cmd_num, &offset, env);
// 	}
// 	return (0);
// }

/////////////////////////////////////////

// static void	free_cmd(char ***token)
// {
// 	int	i;

// 	i = 0;
// 	while (token[1][i] != NULL)
// 	{
// 		free(token[1][i]);
// 	}
// 	free(token[1]);
// }

char	*find_last(char *str, int flag)
{
	if (*str >= '0' && *str <= '9' && flag == 1)
		return (str + 1);
	while (*str != '\0' && *str != '$')
	{
		str++;
	}
	return (str);
}

char	*get_env_name(char *cmd, char *last, char **env)
{
	char	*env_name;
	char	*temp;

	env_name = (char *)malloc(sizeof(char) * (last - cmd + 1));
	if (env_name == NULL)
		perror_and_exit("malloc", 1);
	ft_memset(env_name, 0, (last - cmd + 1));
	ft_memcpy(env_name, cmd, last - cmd);
	temp = get_env(env_name, env);
	free(env_name);
	return (temp);
}

char	*dup_with_len(char *str, char *last)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (last - str + 1));
	if (result == NULL)
		perror_and_exit("malloc", 1);
	ft_memset(result, 0, (last - str + 1));
	ft_memcpy(result, str, last - str);
	return (result);
}

char	*line_expand(char *cmd, char **env)
{
	char	*last;
	char	*temp;
	char	*env_var;
	char	*result;

	result = (char *)malloc(sizeof(char));
	if (result == NULL)
		perror_and_exit("malloc", 1);
	*result = '\0';
	while (*cmd != '\0')
	{
		if (*cmd == '$')
		{
			last = find_last(++cmd, 1);
			env_var = get_env_name(cmd, last, env);
			cmd = last;
			if (env_var != NULL)
			{
				temp = mi_strjoin(result, env_var);
				free(result);
				free(env_var);
				result = temp;
			}
		}
		else
		{
			last = find_last(cmd, 0);
			env_var = dup_with_len(cmd, last);
			temp = mi_strjoin(result, env_var);
			free(result);
			free(env_var);
			result = temp;
			cmd = last;
		}
	}
	return (result);
}

// char	*line_expand_flags(char *cmd, char **env)
// {

// }

char	*join_all_cmd(char ***token, char **env)
{
	int		index;
	char	*cmds_temp;
	char	*expanded;
	//char	*flags_temp;
	char	*result;

	index = 0;
	expanded = line_expand(token[1][index], env);
	result = mi_strjoin("", expanded);
	free(expanded);
	//flags_out = mi_strjoin("", line_expand_flags(token[1][index], env));
	while (token[1][++index] != NULL)
	{
		expanded = line_expand(token[1][index], env);
		cmds_temp = mi_strjoin(result, expanded);
		//flags_temp = mi_strjoin(flags_temp, line_expand_flags(token[1][index], env));
		free(result);
		free(expanded);
		//free(flags_out);
		result = cmds_temp;
		//flags_out = flags_temp;
	}
	return (result);
}

// char	**re_tokenize(char ***token, char **env)
// {
// 	//char	*flags;
// 	char	*str;
// 	char	**cmds;

// 	//join all cmd and expand
// 	str = join_all_cmd(token, env);
// 	//count_cmd
// 	//malloc cmds
// 	//tokenize_cmd(str, cmds);
// }

void	cmd_expand(char ***token, char **env)
{
	//char	**cmd;
	char	*str;

	//if (!is_expand_needed())
	//	return ;
	str = join_all_cmd(token, env);
	printf("join\n%s\n", str);
	free(str);
	//cmd = re_tokenize(token, env);
	//free token[1]
	//free_cmd(token);
	//add token[1]
	//token[1] = cmd;
}
