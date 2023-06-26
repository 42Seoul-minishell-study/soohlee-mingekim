/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:42 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 20:32:32 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	tokens_print(char *****tokens)
// {
// 	int	pipe;
// 	int	i;
// 	int	j;

// 	pipe = -1;
// 	while ((*tokens)[++pipe])
// 	{
// 		i = -1;
// 		while ((*tokens)[pipe][++i])
// 		{
// 			j = -1;
// 			while ((*tokens)[pipe][i][++j])
// 				printf("%d %d %d: %s\n", pipe, i, j, (*tokens)[pipe][i][j]);
// 		}
// 	}
// }

int	translation(char *****tokens, char **envp)
{
	if (*tokens == NULL)
		return (0);
	shell_expand(tokens, envp);
	//tokens_print(tokens);
	return (0);
}
