/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:59:10 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/21 16:57:18 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "getcwd: error\n", 15);
		g_exit_status = 1;
		return (0);
	}
	printf("%s\n", path);
	free(path);
	g_exit_status = 0;
	return (0);
}
