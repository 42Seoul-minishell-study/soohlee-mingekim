/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:52:26 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/17 16:25:48 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpreter(char *out_str, char **envp)
{
	char	****data;

	translation(out_str, &data, envp);	//sooha
//	execute(data, envp);				//minkeun
	if (envp)
		;
	return (0);
}
