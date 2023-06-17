/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:05:31 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/17 19:01:03 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_c_handler(int signum)
{
	if (g_exit_status == -2)
	{
		write(2, "> \n", 3);
		close(1);
		close(0);
		g_exit_status = -3;
		return ;
	}
	if (signum)
		;
	g_exit_status = CTRL_C;
	close(0);
	close(1);
	// rl_replace_line("", 0); //readline 입력값 수정 함수.
	// rl_on_new_line();	//readline prompt출력 위치 한줄 내리는 역할하는 함수.
	// write(1, "M_\n", 3);
	// rl_redisplay(); //readline prompt 재출력 함수, readline 입력값 존재시 같이 출력함.
}

int	stdin_dup(int *stdinout_copy)
{
	stdinout_copy[0] = dup(STDIN_FILENO);
	stdinout_copy[1] = dup(STDOUT_FILENO);
	stdinout_copy[CTRL_C_COUNT] = 0;
	return (0);
}

int	stdin_dup2(int *stdinout_copy)
{
	if (g_exit_status == CTRL_C)
	{
		dup2(stdinout_copy[0], STDIN_FILENO);
		dup2(stdinout_copy[1], STDOUT_FILENO);
		if (stdinout_copy[CTRL_C_COUNT] == 0)
			write(1, "\n", 1);
		stdinout_copy[CTRL_C_COUNT]++;
		g_exit_status = 1;
		return (0);
	}
	else
		stdinout_copy[CTRL_C_COUNT] = 0;
	return (1);
}

//when ctrl-D set g_exit_status to -4