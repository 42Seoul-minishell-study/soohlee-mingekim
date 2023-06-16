/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/16 17:19:51 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**env;
	int		stdin_copy;
	int		stdout_copy;
	int		ctrl_cnt;

	ctrl_cnt = 0;
	stdin_copy = dup(0);
	stdout_copy = dup(1);
	args_check(argc, argv, envp);
	set_signal();
	env = set_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		if (g_exit_status == 1)
		{
			dup2(stdin_copy, 0);
			dup2(stdout_copy, 1);
			if (ctrl_cnt == 0)
				write(1, "\n", 1);
			g_exit_status = 0;
			ctrl_cnt++;
			continue ;
		}
		else
			ctrl_cnt = 0;
		tokens = tokenize(str);
		if (!tokens)
			break ;
		translation(&tokens, env);
		execute(tokens, &env, &ctrl_cnt);
		heredoc_unlink(tokens);
		free_tokens(&tokens);
		add_history(str);
		free(str);
	}
	free_env(&env);
	return (0);
}
