/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:05:31 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/15 14:46:44 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_c_handler(int signum)
{
	if (g_exit_status == -2)
	{
		write(1, "\n", 1);
		close(0);
		g_exit_status = -3;
		return ;
	}
	if (signum)
		;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}
