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

int	shell_expand(char *****out_data, char **envp)
{
	int	procces_idx;

	procces_idx = -1;
	while ((*out_data)[++procces_idx])
	{
		redirection_expand(&((*out_data)[procces_idx][0]), envp);
		cmd_expand(&((*out_data)[procces_idx][1]), envp);
	}
	return (0);
}
