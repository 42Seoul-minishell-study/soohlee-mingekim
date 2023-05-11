/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:29:27 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:12:06 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_loop_prompt(int argc, char **argv, char **envp)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			my_free_exit(EXIT);
		add_history(input);
	}
	if (argc || argv || envp)
		;
}
