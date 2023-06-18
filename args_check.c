/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:18:48 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 15:26:24 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_check(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_putstr_fd("Invalid Argument : too many Argument\n", 2);
		exit (1);
	}
	else if (!argv)
	{
		ft_putstr_fd("Invalid Argument : Argument is NULL\n", 2);
		exit (1);
	}
	else if (!envp)
	{
		ft_putstr_fd("Invalid Argument : Invalid envp\n", 2);
		exit (1);
	}
	return (0);
}

//minishell에 대한 access 체크 (access함수)