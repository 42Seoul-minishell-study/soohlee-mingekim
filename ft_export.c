/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:46 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/26 20:27:33 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_export(char *argv, char ***env)
{
	char	*value;
	char	*name;

	if (ft_strchr(argv, '='))
		name = mi_substr(argv, 0, ft_strchr(argv, '=') - argv);
	else
		return (only_name_add(argv, env));
	value = get_env(name, *env);
	if (!value)
		add_env(argv, env);
	else
	{
		one_d_free_null(&value);
		delete_env(name, env, 0);
		add_env(argv, env);
	}
	one_d_free_null(&name);
	g_exit_status = 0;
	return (0);
}

static int	is_export_str(char *s)
{
	char	*temp;

	temp = s;
	if (*temp == '=' || ft_isdigit(*temp))
	{
		ft_putstr_fd("export: \'", 2);
		error_exit_status(s, 1);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (1);
	}
	while (*temp)
	{
		if (*temp == '=')
			return (0);
		if (!ft_isalnum(*temp) && *temp != '_')
		{
			ft_putstr_fd("export: \'", 2);
			error_exit_status(s, 1);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (1);
		}
		temp++;
	}
	return (0);
}

static int	print_export(char **env)
{
	int				i;
	int				j;
	int				sort_i;
	int				sort_hash[1024];

	ft_memset(sort_hash, 0, sizeof(int) * 1024);
	make_sort_hash(sort_hash, env);
	sort_i = -1;
	while (++sort_i < 1028)
	{
		i = -1;
		while (env[++i])
		{
			if (!(sort_hash[sort_i] == 1 && sort_i == (int)env[i][0]))
				continue ;
			j = -1;
			print_export_oneline(env, &i, &j);
		}
	}
	return (0);
}

int	ft_export(char **argv, char ***env)
{
	char	**temp;
	int		flag;

	g_exit_status = 0;
	if (!*(++argv))
		return (print_export(*env));
	temp = argv;
	flag = 0;
	if (*temp && *temp[0] == '-')
	{
		ft_putstr_fd("export: ", 2);
		while (*temp && !ft_isalnum(temp[0][flag]))
			write(2, &(temp[0][flag++]), 1);
		error_exit_status(": invalid option\n", 2);
		return (0);
	}	
	while (*argv)
	{
		g_exit_status = is_export_str(*argv);
		if (g_exit_status == 0)
			add_export(*argv, env);
		argv++;
	}
	return (0);
}
