/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/17 19:06:38 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**env;
	int		stdinout_copy[3];

	stdin_dup(stdinout_copy);
	args_check(argc, argv, envp);
	set_signal();
	env = set_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		if (!stdin_dup2(stdinout_copy))
			continue ;
		if (str == NULL) //ctrl-D
			break ;
		if (g_exit_status == -4) //ctrl-D
			exit(0);
		if (*str == '\0')
		{
			free(str);
			continue ;
		}
		tokens = tokenize(str);
		if (tokens == NULL)
		{
			add_history(str);
			free(str);
			continue ;
		}
		translation(&tokens, env);
		execute(tokens, &env, stdinout_copy);
		free_tokens(&tokens);
		add_history(str);
		free(str);
	}
	free_env(&env);	//ctrl-D 후 여기서 abort error 뜸
	return (0);
}
