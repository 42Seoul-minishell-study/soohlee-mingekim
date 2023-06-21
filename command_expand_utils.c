/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:04:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/21 18:45:16 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mid_insert(t_retoken *db, char ***new_cmd, int *i, int *insert_idx)
{
	if (db->front_space_exist == 0)
		(*new_cmd)[(*i)++] = \
			mi_strjoin(db->front, db->insert_twod[(*insert_idx)++]);
	else
		(*new_cmd)[(*i)++] = mi_strdup(db->front);
	while (db->insert_twod[(*insert_idx) + 1])
		(*new_cmd)[(*i)++] = \
			mi_strdup(db->insert_twod[(*insert_idx)++]);
	if (db->tail_space_exist == 0 && (*new_cmd)[(*i)] != NULL)
	{
		(*new_cmd)[(*i)++] = \
				mi_strjoin(db->insert_twod[(*insert_idx)], db->end);
		if (ft_strlen(db->insert_twod[(*insert_idx)]) == 0)
			*(db->offset) = db->start;
		else
			*(db->offset) = \
				db->start + ft_strlen(db->insert_twod[(*insert_idx)]) - 1;
		insert_idx++;
		return (0);
	}
	(*new_cmd)[(*i)++] = mi_strdup(db->insert_twod[(*insert_idx)]);
	(*new_cmd)[(*i)++] = mi_strdup(db->end);
	*(db->offset) = db->start + ft_strlen(db->insert_twod[(*insert_idx)++]) - 1;
	return (0);
}

static int	insert_two_d_array(char ***tokens, t_retoken db)
{
	char	**new_cmd;
	int		new_cmd_num;
	int		tokens_idx;
	int		insert_idx;

	new_cmd = (char **)malloc(sizeof(char *) * (db.cmdtotal + db.twod_len + 1));
	if (!new_cmd)
		exit (1);
	new_cmd_num = 0;
	tokens_idx = 0;
	insert_idx = 0;
	while (new_cmd_num < *(db.cmd_num))
		new_cmd[new_cmd_num++] = mi_strdup((*tokens)[tokens_idx++]);
	tokens_idx++;
	mid_insert(&db, &new_cmd, &new_cmd_num, &insert_idx);
	*(db.cmd_num) = new_cmd_num - 1;
	while ((*tokens)[tokens_idx])
		new_cmd[new_cmd_num++] = mi_strdup((*tokens)[tokens_idx++]);
	new_cmd[new_cmd_num] = NULL;
	two_d_free_null(&(*tokens));
	*tokens = new_cmd;
	new_cmd = NULL;
	return (0);
}

int	re_tokenize(char ***tokens, t_retoken db, char *out_insert_str)
{
	while ((*tokens)[db.cmdtotal++])
		;
	db.front = mi_substr((*tokens)[*(db.cmd_num)], 0, db.start);
	db.end = mi_substr((*tokens)[*(db.cmd_num)], *(db.offset), -1);
	if (out_insert_str[0] == ' ' && ((*(db.cmd_num) != 0) \
		|| (*tokens)[*(db.cmd_num)][0] != '\0'))
		db.front_space_exist = 1;
	if (ft_strlen(out_insert_str) >= 2 \
		&& out_insert_str[ft_strlen(out_insert_str) - 2] == ' ' && \
			db.last_flag == 0)
		db.tail_space_exist = 1;
	db.insert_twod = ft_split(out_insert_str, ' ');
	if (db.insert_twod[1] != 0)
		db.start = 0;
	while (db.insert_twod[db.twod_len++])
		;
	db.twod_len = db.twod_len + db.front_space_exist + db.tail_space_exist;
	insert_two_d_array(tokens, db);
	two_d_free_null(&(db.insert_twod));
	one_d_free_null(&db.front);
	one_d_free_null(&db.end);
	return (2);
}
