/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:34:21 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/26 15:34:28 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(char ***token)
{
	int	i;

	i = 0;
	while (token[1][i] != NULL)
	{
		free(token[1][i]);
		i++;
	}
	free(token[1]);
}

char	*join_all_cmd(char ***token, char **env)
{
	int		index;
	char	*cmds_temp;
	char	*expanded;
	char	*result;

	index = 0;
	line_expand(&token[1][index], env, BEFORE_TOKENIZE);
	expanded = mi_strdup(token[1][index]);
	result = mi_strjoin("", expanded);
	free(expanded);
	while (token[1][++index] != NULL)
	{
		line_expand(&token[1][index], env, BEFORE_TOKENIZE);
		expanded = mi_strdup(token[1][index]);
		cmds_temp = mi_strjoin(result, expanded);
		free(result);
		free(expanded);
		result = cmds_temp;
	}
	return (result);
}
