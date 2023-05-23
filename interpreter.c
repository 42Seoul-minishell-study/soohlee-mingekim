/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:52:26 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/22 21:25:28 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpreter(char *out_str, char **envp)
{
	char	***cmds;

	if (envp)
		;
	cmds = NULL;
	if (cmds == NULL)
		return (0);
	if (out_str == NULL)
		return (0);
	return (1);
}
