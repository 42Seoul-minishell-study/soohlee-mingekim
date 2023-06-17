/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 00:43:37 by soohlee          ###   ########.fr       */
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
		if (str == NULL_CTRL_D) //ctrl-D
		{
			printf("asdf\n");
			if (waitpid(0, &g_exit_status, WNOHANG) == 0) //자식이 한명이라도 끝나지 않았다면 WNOHANG옵션에 의해 0반환함.
				continue ;
			g_exit_status = 0;
			break ;
		}
		if (g_exit_status == -4) //ctrl-D
			exit(0);
		if (*str == '\0') //enter만 들어왔을때 처리
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
		add_history(str);
		execute(tokens, &env, stdinout_copy);
		free_tokens(&tokens);
		free(str);
	}
	free_env(&env);	//ctrl-D 후 여기서 abort error 뜸
	return (0);
}
