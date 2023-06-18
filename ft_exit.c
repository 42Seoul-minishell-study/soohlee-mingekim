/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:27:34 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 14:37:32 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv, char ***env)
{
	printf("exit\n");
	if (argv[1])
	g_exit_status = ft_atoi(argv[1]);
	two_d_free_null(&(*env));
	exit (g_exit_status);
	return (0);
}
