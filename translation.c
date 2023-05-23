/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:53:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/23 02:33:21 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_print(char *****out_data);

int	translation(char *****out_data, char **envp)
{	
	shell_expand(out_data, envp);
	tokens_print(out_data);//임시결과확인용
	if (envp)
		;
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
