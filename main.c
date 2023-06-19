/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/19 14:45:49 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	asdf(void)
{
	ft_putstr_fd("atexit: ", 2);
	system("leaks minishell | grep process");
	ft_putstr_fd("\n", 2);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**env;
	int		stdinout_copy[3];

	if (!stdin_dup(stdinout_copy) && !args_check(argc, argv, envp))
		set_signal();
	env = set_env(envp);
	while (1)
	{
		system("leaks minishell");
		str = readline("\U0001F60Aminishell$ ");
		if (!stdin_dup2(stdinout_copy) || ctrl_d_continue(str))
			continue ;
		else if (str == NULL)
			break ;
		else if (*str == '\0' && !one_d_free_null(&str))
			continue ;
		tokens = tokenize(str);
		if (!one_d_free_null(&str) && tokens == NULL)
			continue ;
		translation(&tokens, env);
		execute(&tokens, &env, stdinout_copy);
	}
	free_env(&env);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	char	****tokens;
// 	char	**env;
// 	int		stdinout_copy[3];

// 	atexit(asdf);
// 	if (!stdin_dup(stdinout_copy) && !args_check(argc, argv, envp))
// 		set_signal();
// 	env = set_env(envp);
// 	while (1)
// 	{
// 		ft_putstr_fd("while: ", 2);
// 		system("leaks minishell | grep process");
// 		ft_putstr_fd("\n", 2);
// 		str = readline("\U0001F60Aminishell$ ");
// 		if (!stdin_dup2(stdinout_copy) || ctrl_d_continue(str))
// 			continue ;
// 		else if (str == NULL)
// 			break ;
// 		else if (*str == '\0' && !one_d_free_null(&str))
// 			continue ;
// 		tokens = tokenize(str);
// 		if (!one_d_free_null(&str) && tokens == NULL)
// 			continue ;
// 		translation(&tokens, env);
// 		execute(&tokens, &env, stdinout_copy);
// 	}
// 	free_env(&env);
// 	ft_putstr_fd("end: ", 2);
// 	system("\nleaks minishell | grep process");
// 	ft_putstr_fd("\n", 2);
// 	return (0);
// }