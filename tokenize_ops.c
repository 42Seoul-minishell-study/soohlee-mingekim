/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:46 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:47 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_split(char **temp, int *len_file_name, int *len_op, int num)
{
	char	*file_name;

	*len_op = num;
	(*temp) += *len_op;
	(*temp) = pass_space(*temp);
	file_name = (*temp);
	(*temp) = find_next_word(*temp);
	*len_file_name = (*temp) - file_name;
	return (file_name);
}

char	*split_ops(char *str, char **op_out)
{
	int		len_op;
	int		len_file_name;
	char	*temp;
	char	*file_name;

	temp = str;
	len_file_name = 0;
	len_op = 0;
	if (ft_strncmp(temp, "<<", 2) == 0)
		file_name = set_split(&temp, &len_file_name, &len_op, 2);
	else if (ft_strncmp(temp, "<", 1) == 0)
		file_name = set_split(&temp, &len_file_name, &len_op, 1);
	else if (ft_strncmp(temp, ">>", 2) == 0)
		file_name = set_split(&temp, &len_file_name, &len_op, 2);
	else if (ft_strncmp(temp, ">", 1) == 0)
		file_name = set_split(&temp, &len_file_name, &len_op, 1);
	*op_out = malloc(sizeof(char) * (len_op + 1 + len_file_name + 1));
	if (*op_out == NULL)
		perror_and_exit("malloc", 1);
	ft_memcpy(*op_out, str, len_op);
	(*op_out)[len_op] = ' ';
	ft_memcpy(*op_out + len_op + 1, file_name, len_file_name);
	(*op_out)[len_op + 1 + len_file_name] = '\0';
	return (temp);
}
