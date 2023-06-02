/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/02 20:49:07 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	test_builtin(char ****tokens, char ***env)

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**env;

	args_check(argc, argv, envp);
	set_signal();
	env = set_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		tokens = tokenize(str);
		if (!tokens)
			break ;
		translation(&tokens, env);
		heredoc(tokens, env);
		execute(tokens, env);
		heredoc_unlink(tokens);
		free_tokens(&tokens);
		add_history(str);
		free(str);
	}
	free_env(&env);
	return (0);
}

// static void	test_builtin(char ****tokens, char ***env)
// {
// 	char	**argv;

// 	argv = tokens[0][1];
// 	if (!ft_strncmp(argv[0], "cd", 3))
// 		ft_cd(argv, env);
// 	else if (!ft_strncmp(argv[0], "pwd", 4))
// 		ft_pwd();
// 	else if (!ft_strncmp(argv[0], "echo", 5))
// 		ft_echo(argv);
// 	else if (!ft_strncmp(argv[0], "env", 4))
// 		ft_env(*env);
// 	else if (!ft_strncmp(argv[0], "export", 7))
// 		ft_export(argv, env);
// 	else if (!ft_strncmp(argv[0], "unset", 6))
// 		ft_unset(argv, env);
// }
