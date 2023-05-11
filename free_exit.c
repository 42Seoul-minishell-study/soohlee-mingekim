/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:25:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/11 15:51:22 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(int flag)
{
	exit_print(flag);
	exit (0);
}

void	exit_print(int flag)
{
	if (flag == EXIT)
	{
		rl_on_new_line();
		ft_putstr_fd("\x1b[1A", STDOUT);
		ft_putstr_fd("\033[11C", STDOUT);
		ft_printf("exit\n");
	}
}
