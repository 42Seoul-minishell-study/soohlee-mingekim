/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_expand_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:34:32 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/26 17:28:52 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_single_quote(char **cmd, int *offset)
{
	char	*temp;
	char	*last;

	temp = (*cmd) + *offset;
	last = temp;
	last = find_next_single_quote(last);
	*offset += last - temp;
}

void	skip_double_quote(char **cmd, int *offset)
{
	char	*temp;
	char	*last;

	temp = (*cmd) + *offset;
	last = temp;
	last = find_next_double_quote(last);
	*offset += last - temp;
}

char	*expand_exit_status(char *str)
{
	char	*exit_status_str;
	char	*new_str;

	exit_status_str = ft_itoa(g_exit_status);
	if (!exit_status_str)
		perror_and_exit("malloc error\n", 1);
	new_str = mi_strjoin(exit_status_str, str + 2);
	one_d_free_null(&exit_status_str);
	return (new_str);
}
