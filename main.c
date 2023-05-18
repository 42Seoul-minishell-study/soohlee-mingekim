/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/11 15:52:05 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	****tokens;
	char	*str;

	while (1)
	{
		str = readline(PROMPT);
		if (str)
			tokens = tokenize(str);
		add_history(str);
		free(str);
	}
	// operator_process(cmds, envp);
	// args_check(argc, argv, envp);
	// set_signal();
	// loop_prompt(argc, argv, envp);
	return (0);
}
