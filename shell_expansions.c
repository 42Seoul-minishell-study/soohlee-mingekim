/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:29:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/21 15:04:45 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_expansions(char *****out_data, char **envp)
{
	int	procces_idx;

	procces_idx = -1;
	while ((*out_data)[++procces_idx])
	{
		redirection_expansions(&((*out_data)[procces_idx][0]), envp);
		cmd_expansions(&((*out_data)[procces_idx][1]), envp);
	}
	return (0);
}
