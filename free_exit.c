/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:25:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 20:24:57 by mingekim         ###   ########.fr       */
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

void two_d_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
}
