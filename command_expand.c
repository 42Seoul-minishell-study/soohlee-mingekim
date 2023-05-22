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
		cmd_line_expand(&((*out_cmd)[cmd_num]), envp);
	if (envp)
		;
	return (0);
}

int	cmd_line_expand(char **out_one_line, char **envp)
{
	int		offset;
	char	*out_one_line_temp;

	offset = -1;
	while ((*out_one_line)[++offset])
	{
		if ((*out_one_line)[offset] == '\'')
			single_quate(out_one_line, &offset, envp);
		else if ((*out_one_line)[offset] == '\"')
			double_quate(out_one_line, &offset, envp);
		else if ((*out_one_line)[offset] == '$')
			env_trans(out_one_line, &offset, envp);
	}
	out_one_line_temp = *out_one_line;
	*out_one_line = ft_strtrim(out_one_line_temp, " ");
	free(out_one_line_temp);
	out_one_line_temp = 0;
	return (0);
}
