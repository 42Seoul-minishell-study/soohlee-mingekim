/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:27:34 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/21 13:40:22 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_isspace_sign(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] >= 9 && argv[i] <= 13)
		i++;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i++]))
			return (0);
	}
	while (argv[i] && argv[i] >= 9 && argv[i] <= 13)
		i++;
	if (argv[i] == '\0')
		return (1);
	return (0);
}

int	ft_exit(char **argv, char ***env)
{
	g_exit_status = 0;
	ft_putstr_fd("exit\n", 2);
	if (argv[1] == NULL)
	{
		two_d_free_null(&(*env));
		exit(g_exit_status);
	}
	if (skip_isspace_sign(argv[1]))
	{
		if (argv[2] != NULL)
		{
			ft_putstr_fd("too many arguments\n", 2);
			g_exit_status = 1;
			two_d_free_null(&(*env));
			exit (1);
		}
		g_exit_status = ft_atoi(argv[1]);
		two_d_free_null(&(*env));
		exit(g_exit_status);
	}
	ft_putstr_fd("numeric argument required\n", 2);
	two_d_free_null(&(*env));
	g_exit_status = 255;
	exit (g_exit_status);
	return (0);
}
