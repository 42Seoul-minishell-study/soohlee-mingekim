/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:10:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/22 15:20:41 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	move_path(char **cur_path, char ***indepen_env)
{
	char	*pull_path;

	pull_path = mi_strjoin("OLDPWD=", *cur_path);
	one_d_free_null(&(*cur_path));
	change_env(pull_path, "OLDPWD", indepen_env);
	one_d_free_null(&pull_path);
	*cur_path = getcwd(NULL, 0);
	if (!(*cur_path))
		return (error_exit_status("getcwd: error\n", 1));
	pull_path = mi_strjoin("PWD=", *cur_path);
	one_d_free_null(&(*cur_path));
	change_env(pull_path, "PWD", indepen_env);
	one_d_free_null(&pull_path);
	g_exit_status = 0;
	return (0);
}

static int	move_path_check(char *argv, char ***indepen_env)
{
	char	*cur_path;

	if (!access(argv, F_OK))
	{
		cur_path = getcwd(NULL, 0);
		if (!cur_path)
			return (error_exit_status("getcwd: error\n", 1));
		if (chdir(argv))
		{
			g_exit_status = 1;
			one_d_free_null(&cur_path);
			write(2, "cd: ", 4);
			perror(argv);
			return (0);
		}
		else
			move_path(&cur_path, indepen_env);
		return (0);
	}
	g_exit_status = 1;
	return (error_print("cd: ", argv, \
		": No such file or directory\n"));
	return (0);
}

static int	old_path_move(char ***indepen_env)
{
	char	*move_path;
	char	*cur_path;
	char	*new_path;

	move_path = get_env("OLDPWD", *indepen_env);
	if (!move_path || ft_strlen(move_path) == 0)
		if (!move_path || !one_d_free_null(&move_path))
			return (error_exit_status("cd: OLDPWD not set\n", 1));
	cur_path = getcwd(NULL, 0);
	if (chdir(move_path) && !one_d_free_null(&cur_path) && \
		!one_d_free_null(&move_path))
		return (error_exit_status("chdir: error\n", 1));
	new_path = mi_strjoin("OLDPWD=", cur_path);
	one_d_free_null(&cur_path);
	change_env(new_path, "OLDPWD", indepen_env);
	one_d_free_null(&new_path);
	new_path = mi_strjoin("PWD=", move_path);
	one_d_free_null(&move_path);
	change_env(new_path, "PWD", indepen_env);
	one_d_free_null(&new_path);
	return (ft_pwd());
}

static int	home_path_move(char ***indepen_env)
{
	char	*cur_path;
	char	*move_path;
	char	*pull_path;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
		return (error_exit_status("getcwd: error\n", 1));
	pull_path = mi_strjoin("OLDPWD=", cur_path);
	one_d_free_null(&cur_path);
	change_env(pull_path, "OLDPWD", indepen_env);
	one_d_free_null(&pull_path);
	move_path = get_env("HOME", *indepen_env);
	if (!move_path)
		return (error_exit_status("getenv: error\n", 1));
	if (chdir(move_path) && !one_d_free_null(&move_path))
		return (error_exit_status("chdir: error\n", 1));
	pull_path = mi_strjoin("PWD=", move_path);
	one_d_free_null(&move_path);
	change_env(pull_path, "PWD", indepen_env);
	one_d_free_null(&pull_path);
	g_exit_status = 0;
	return (0);
}

int	ft_cd(char **argv, char ***indepen_env)
{
	g_exit_status = 0;
	argv++;
	if (!*argv || !ft_strlen(*argv) || (!ft_strncmp(*argv, "~\0", 2) \
		&& argv[1] == NULL))
		return (home_path_move(indepen_env));
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
	{
		change_home(&(*argv), *indepen_env);
		return (move_path_check(*argv, indepen_env));
	}
	return (0);
}
