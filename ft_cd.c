/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:10:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/27 02:40:51 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error_print(int flag);
int	home_path_move(char **indepen_env);

int	ft_cd(char **argv, char **indepen_env)
{
	argv++;
	if (!argv || !ft_strlen(*argv) || ft_strncmp(*argv, "~\0", 2))
		return (home_path_move(indepen_env));
	// if (ft_strlen(*argv) == 2 && ft_strncmp(*argv, "--", 2))
	// 	argv++;
	// if (ft_strlen(*argv) >= 3 && ft_strncmp(*argv, "--", 2))
	// 	return (cd_error_print(0));
	// if (ft_strncmp(*argv, "-\0", 2))
	// 	return (old_path_move("arg"));
	// if (ft_strncmp(*argv, ".", 1))
	// 	return (relative_path_move("arg"));
	// if (ft_strncmp(*argv, "/", 1))
	// 	return (absolute_path_move("arg"));
	return (0);
}

int	cd_error_print(int flag)
{
	if (flag == 0)
		ft_putstr_fd("cd: --: invalid option", 2);
	return (1);
}

int	home_path_move(char **indepen_env)
{
	char	*path;

	path = get_env("HOME\0", indepen_env);
	chdir(path);
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

// [] : home path 
// [--] : non option
// [-] : oldpath로 이동후 pwd실행
// [.] , [..] : relative path
// [/] : absolute path
