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
		execute(tokens, &env);
		heredoc_unlink(tokens);
		free_tokens(&tokens);
		add_history(str);
		free(str);
	}
	free_env(&env);
	return (0);
}
