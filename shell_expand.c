/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:29:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/23 01:16:49 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_expand(char *****tokens, char **env)
{
	int	idx;

	idx = -1;
	while ((*tokens)[++idx])
	{
		redirection_expand(&((*tokens)[idx][0]), env);
		cmd_expand((*tokens)[idx], env);
	}
	return (0);
}
