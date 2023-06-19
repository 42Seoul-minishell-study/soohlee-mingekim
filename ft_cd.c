/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:10:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 01:14:59 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	home_path_move(char ***indepen_env);
int	old_path_move(char ***indepen_env);
int	move_path(char *argv, char ***indepen_env);
int	change_env(char *new_str, char *del_name, char ***indepen_env);

int	ft_cd(char **argv, char ***indepen_env)
{
	argv++;
	if (!*argv || !ft_strlen(*argv) || !ft_strncmp(*argv, "~\0", 2))
	{
		home_path_move(indepen_env);
		return (0);
	}
	if (ft_strlen(*argv) == 2 && !ft_strncmp(*argv, "--", 2))
		argv++;
	if (ft_strlen(*argv) >= 3 && !ft_strncmp(*argv, "--", 2))
	{
		g_exit_status = 1;
		return (1 && write(2, "cd: --: invalid option\n", 23));
	}
	if (ft_strlen(*argv) >= 1 && !ft_strncmp(*argv, "-\0", 2))
		return (old_path_move(indepen_env));
	else
		return (move_path(*argv, indepen_env));
	return (0);
}

int	home_path_move(char ***indepen_env)
{
	char	*cur_path;
	char	*move_path;
	char	*pull_path;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
		exit(1);
	pull_path = mi_strjoin("OLDPWD=", cur_path);
	one_d_free_null(&cur_path);
	change_env(pull_path, "OLDPWD", indepen_env);
	one_d_free_null(&pull_path);
	move_path = get_env("HOME", *indepen_env);
	if (!move_path)
		move_path = mi_strdup("");
	chdir(move_path);
	pull_path = mi_strjoin("PWD=", move_path);
	one_d_free_null(&move_path);
	change_env(pull_path, "PWD", indepen_env);
	one_d_free_null(&pull_path);
	return (0);
}

int	old_path_move(char ***indepen_env)
{
	char	*move_path;
	char	*cur_path;
	char	*new_path;

	move_path = get_env("OLDPWD", *indepen_env);
	if (!move_path)
		return (1 && write(2, "cd: OLDPWD not set\n", 19));
	cur_path = getcwd(NULL, 0);
	if (chdir(move_path))
		exit(write(2, "chdir_error\n", 12));
	new_path = mi_strjoin("OLDPWD=", cur_path);
	one_d_free_null(&cur_path);
	change_env(new_path, "OLDPWD", indepen_env);
	one_d_free_null(&new_path);
	new_path = mi_strjoin("PWD=", move_path);
	one_d_free_null(&move_path);
	change_env(new_path, "PWD", indepen_env);
	one_d_free_null(&new_path);
	return (0);
}

int	move_path(char *argv, char ***indepen_env)
{
	char	*cur_path;
	char	*pull_path;

	if (!access(argv, F_OK))
	{
		cur_path = getcwd(NULL, 0);
		if (chdir(argv))
		{
			write(2, "cd: ", 4);
			write(2, argv, ft_strlen(argv));
			write(2, ": Not a directory\n", 19);
			g_exit_status = 1;
			if (!cur_path)
				cur_path = mi_strdup("");
			one_d_free_null(&cur_path);
			return (0);
		}
		else
		{
			pull_path = mi_strjoin("OLDPWD=", cur_path);
			one_d_free_null(&cur_path);
			change_env(pull_path, "OLDPWD", indepen_env);
			one_d_free_null(&pull_path);
			cur_path = getcwd(NULL, 0);
			if (!cur_path)
				cur_path = mi_strdup("");
			pull_path = mi_strjoin("PWD=", cur_path);
			one_d_free_null(&cur_path);
			change_env(pull_path, "PWD", indepen_env);
			one_d_free_null(&pull_path);
		}
		return (0);
	}
	write(2, "cd: ", 4);
	write(2, argv, ft_strlen(argv));
	write(2, ": No such file or directory\n", 29);
	g_exit_status = 1;
	return (0);
}

int	change_env(char *new_str, char *del_name, char ***indepen_env)
{
	delete_env(del_name, indepen_env);
	add_env(new_str, indepen_env);
	return (0);
}

// [] : home path 
// [--] : non option
// [-] : oldpath로 이동후 pwd실행
// [.] , [..] : relative path
// [/] : absolute path
