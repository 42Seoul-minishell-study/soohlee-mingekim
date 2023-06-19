/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:03:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/19 23:38:16 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	flag;

	flag = 1;
	if (ft_strncmp(*argv++, "echo\0", 5))
		return (1);
	if (*argv == NULL)
	{
		g_exit_status = 0;
		return (printf("\n"));
	}
	if (!ft_strncmp(*argv, "-n", 2))
		flag = option_remove(&argv);
	ehco_print(argv);
	if (flag == 1)
		printf("\n");
	g_exit_status = 0;
	return (0);
}

int	option_remove(char ***argv)
{
	int	i;
	int	flag;

	flag = 1;
	while (*argv && !ft_strncmp(**argv, "-n", 2))
	{
		i = 0;
		while ((**argv)[++i] == 'n')
			;
		if ((**argv)[i] == '\0')
		{
			flag = 0;
			*argv = (*argv + 1);
			continue ;
		}
		return (flag);
	}
	flag = 0;
	return (flag);
}

int	ehco_print(char **argv)
{
	int	flag;

	flag = 1;
	if ((*argv)[0] == '\0')
		flag = 0;
	printf("%s", *argv++);
	while (*argv)
	{
		if (flag == 1)
			printf(" ");
		if ((*argv)[0] == '\0')
			flag = 0;
		printf("%s", *argv++);
		flag = 1;
	}
	return (0);
}
