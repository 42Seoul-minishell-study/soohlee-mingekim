/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:42 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 16:29:10 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_print(char *****out_data);

int	translation(char *****out_data, char **envp)
{
	if (*out_data == NULL)
		return (0);
	shell_expand(out_data, envp);
	tokens_print(out_data);
	return (0);
}

void	tokens_print(char *****out_data)
{
	int	pipe;
	int	i;
	int	j;

	pipe = -1;
	printf("---------------------------expantion-----------------------------\n");
	while ((*out_data)[++pipe])
	{
		i = -1;
		while ((*out_data)[pipe][++i])
		{
			j = -1;
			while ((*out_data)[pipe][i][++j])
				printf("%d %d %d: %s\n", pipe, i, j, (*out_data)[pipe][i][j]);
		}
	}
}
