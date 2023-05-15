/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:52:26 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/15 17:18:50 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpreter(char **out_str, char **envp)
{
	char	***data;

	data = NULL;
	parsing (out_str, &data, envp);	//sooha
//	pipe_and_fork (&data);				//minkeun
	data = NULL;
//	out_str = NULL;
	if (envp)
		;
	return (0);
}
