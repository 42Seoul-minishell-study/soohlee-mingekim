/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/27 02:10:36 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**indepen_env;

	indepen_env = set_env(envp);
	// print_env(env);
	while (1)
	{
		str = readline(PROMPT);
		if (str)
		{
			tokens = tokenize(str);
			//when we get <<<< or other error is syntax error (TODO)
			translation(&tokens, indepen_env);
			ft_cd(tokens[0][1], indepen_env);
			//free_all(tokens);
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
	//free_env(&env);
	return (0);
}
