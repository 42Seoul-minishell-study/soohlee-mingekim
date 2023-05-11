/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:05:31 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 01:07:14 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_signal(void)
{
	signal(SIGINT, my_ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	my_ctrl_c_handler(int signum)
{
	if (signum)
		;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}
