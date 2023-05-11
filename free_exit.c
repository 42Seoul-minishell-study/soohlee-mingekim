/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:25:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/05 21:50:04 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_free_exit(int flag)
{
	my_exit_print(flag);
	exit (0);
}

void	my_exit_print(int flag)
{
	if (flag == EXIT)
	{
		rl_on_new_line();
		ft_putstr_fd("\x1b[1A", STDOUT);
		ft_putstr_fd("\033[11C", STDOUT);
		ft_printf("exit\n");
	}
}
