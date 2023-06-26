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

char	*join_with_space(char *front, char *expanded)
{
	char	*space;
	char	*temp;
	char	*result;

	space = mi_strdup(" ");
	if (front == NULL)
	{
		result = mi_strjoin(space, expanded);
		free(space);
		free(expanded);
	}
	else
	{
		temp = mi_strjoin(front, space);
		free(front);
		free(space);
		result = mi_strjoin(temp, expanded);
		free(temp);
		free(expanded);
	}
	return (result);
}

char	*join_all_cmd(char ***token, char **env)
{
	int		index;
	char	*cmds_temp;
	char	*result;

	index = 0;
	line_expand(&token[1][index], env, BEFORE_TOKENIZE);
	result = join_with_space(NULL, mi_strdup(token[1][index]));
	while (token[1][++index] != NULL)
	{
		line_expand(&token[1][index], env, BEFORE_TOKENIZE);
		cmds_temp = join_with_space(result, mi_strdup(token[1][index]));
		result = cmds_temp;
	}
	return (result);
}
