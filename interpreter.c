/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:52:26 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/12 19:10:33 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpreter(char *str, char **envp)
{
	char	***data;

	parsing(str, &data, envp);	//수하
	pipe_and_fork(&data);		//민근쓰
	data = NULL;
	str = NULL;
	if (envp)
		;
	return (0);
}
