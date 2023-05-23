/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/23 01:16:35 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline(PROMPT);
		if (str)
		{
			tokens = tokenize(str);
			translation(&tokens, envp);
		}
		add_history(str);
		free(str);
	}
	if (argc || argv || envp)
		;
	// operator_process(cmds, envp);
	// args_check(argc, argv, envp);
	// set_signal();
	// loop_prompt(argc, argv, envp);
	return (0);
}
