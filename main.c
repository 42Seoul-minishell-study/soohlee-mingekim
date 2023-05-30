/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 15:08:25 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**env;

	env = set_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		if (str != NULL && ft_strlen(str) != 0)
		{
			tokens = tokenize(str);
			if (tokens != NULL)
				translation(&tokens, env);
			//free_all(tokens);
			add_history(str);
		}
		free(str);
	}
	if (argc || argv || envp)
		;
	// operator_process(cmds, envp);
	// args_check(argc, argv, envp);
	// set_signal();
	// loop_prompt(argc, argv, envp);
	//free_env(&env);
	return (0);
}
