/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:10:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/28 14:20:08 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error_print(int flag);
int	home_path_move(char **indepen_env);
int	old_path_move(char **indepen_env);
int relative_path_move(char **argv, char **indepen_env);

int	ft_cd(char **argv, char **indepen_env)
{
	argv++;
	if (!*argv || !ft_strlen(*argv) || !ft_strncmp(*argv, "~\0", 2))
		return (home_path_move(indepen_env));
	if (ft_strlen(*argv) == 2 && !ft_strncmp(*argv, "--", 2))
	 	argv++;
	if (ft_strlen(*argv) >= 3 && !ft_strncmp(*argv, "--", 2))
	 	return (cd_error_print(0));
	if (ft_strlen(*argv) >= 1 && !ft_strncmp(*argv, "-\0", 2))
	 	return (old_path_move(indepen_env));
	if (!ft_strncmp(*argv, ".", 1))
	 	return (relative_path_move(&*argv, indepen_env));
	// if (ft_strncmp(*argv, "/", 1))
	// 	return (absolute_path_move("arg"));
	return (0);
}


//절대경로부터 함수 만들자
//상대경로가 더 까다로움
int relative_path_move(char **argv, char **indepen_env)
{
	char	*temp;

	temp = *argv;
	*argv = ft_substr(temp, 0, ft_strrchr(*argv, '/') - *argv);
	free(temp);
	temp = 0;
	printf("%s\n", *argv);
	if (indepen_env)
		;
	return (0);
}

int	old_path_move(char **indepen_env)
{
	char	*path;

	path = get_env("OLDPWD", indepen_env);
	chdir(path);
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	cd_error_print(int flag)
{
	if (flag == 0)
		ft_putstr_fd("cd: --: invalid option\n", 2);
	return (1);
}

int	home_path_move(char **indepen_env)
{
	char	*path;

	path = get_env("HOME", indepen_env);
	chdir(path);
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

// [] : home path 
// [--] : non option
// [-] : oldpath로 이동후 pwd실행
// [.] , [..] : relative path
// [/] : absolute path
