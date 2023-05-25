/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:03:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/25 15:05:06 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **argv)
{
	int	flag;

	flag = 1;
	if (ft_strncmp(*argv++, "echo\0", 5))
		return (1);
	if (*argv == NULL)
		return (printf("\n"));
	if (!ft_strncmp(*argv, "-n", 2))
		flag = option_remove(&argv);
	while (*argv)
		printf("%s", *argv++);
	if (flag == 1)
		printf("\n");
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
