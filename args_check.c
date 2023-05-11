/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:18:48 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/11 15:51:26 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_check(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_printf("temp_error: args error\n");
		exit (1);
	}
	else if (!argv)
	{
		ft_printf("temp_error: search file dir\n");
		exit (1);
	}
	else if (!envp)
	{
		ft_printf("temp_error_envp is null\n");
		exit (1);
	}
	return (0);
}

//minishell에 대한 access 체크 (access함수)