/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 15:40:16 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_builtin(char ****tokens, char ***env)
{
	char	**argv;

	argv = tokens[0][1];
	if (!ft_strncmp(argv[0], "cd", 3))
		ft_cd(argv, env);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(argv[0], "echo", 5))
		ft_echo(argv);
}

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
			test_builtin(tokens, &env);
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
