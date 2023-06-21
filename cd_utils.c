/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:16:49 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/21 16:57:34 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env(char *new_str, char *del_name, char ***indepen_env)
{
	delete_env(del_name, indepen_env, 0);
	add_env(new_str, indepen_env);
	return (0);
}

int	error_print(char *cmd, char *argv, char *messeage)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(messeage, 2);
	return (0);
}

int	change_home(char **argv, char **env)
{
	char	*home;
	char	*temp;

	if (ft_strlen(*argv) >= 1 && argv[0][0] == '~')
	{
		home = get_env("HOME", env);
		if (!home)
			return (error_exit_status("getenv: error\n", 1));
		temp = *argv;
		*argv = mi_strinsert(temp, home, 0, 0);
		one_d_free_null(&home);
		one_d_free_null(&temp);
	}
	return (0);
}
