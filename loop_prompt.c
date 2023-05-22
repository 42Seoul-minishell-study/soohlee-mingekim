/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:29:27 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/17 16:25:32 by soohlee          ###   ########.fr       */
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
		{
			rl_on_new_line();
			add_history(str);
			interpreter(str, envp);
		}
		else
			free_exit(EXIT);
		free(str);
	}
	if (argc || argv || envp)
		return ;
}
