/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:29:27 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/11 15:59:22 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_prompt(int argc, char **argv, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline(PROMPT);
		if (str)
			interpreter(str);
		else
			free_exit(EXIT);
		add_history(str);
		free(str);
	}
	if (argc || argv || envp)
		return ;
}
