/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:46 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/15 13:39:29 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_export(char *argv, char ***env);
int	print_export(char **env);
int	is_export_str(char *s);
int	make_sort_hash(int *sort_hash, char **env);

int	ft_export(char **argv, char ***env)
{
	char	**temp;
	int		flag;

	if (!argv || !argv[0])
		return (0);
	if (!(*(++argv)))
		return (print_export(*env));
	temp = argv;
	flag = 0;
	while (*temp)
	{
		flag = (1 && is_export_str(*temp));
		temp++;
	}
	if (flag == 1)
		return (1);
	while (*argv)
	{
		add_export(*argv, env);
		argv++;
	}
	return (0);
}

int	add_export(char *argv, char ***env)
{
	char	*value;
	char	*name;

	if (ft_strchr(argv, '='))
		name = ft_substr(argv, 0, ft_strchr(argv, '=') - argv);
	else
		return (only_name_add(argv, env));
	value = get_env(name, *env);
	if (!value)
	{
		add_env(argv, env);
		free(name);
	}
	else
	{
		delete_env(name, env);
		add_env(argv, env);
		free(name);
	}
	return (0);
}

int	print_export(char **env)
{
	int				i;
	int				j;
	int				sort_i;
	int				sort_hash[1028];

	ft_memset(sort_hash, '\0', sizeof(int) * 1028);
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
			while (env[i][++j])
			{
				write(1, &(env[i][j]), 1);
				if (env[i][j] == '=')
					write(1, "\"", 1);
			}
			if (ft_strchr(env[i], '='))
				write(1, "\"\n", 2);
			else
				write(1, "\n", 1);
		}
	}
	return (0);
}

int	is_export_str(char *s)
{
	char	*temp;

	temp = s;
	while (*s && *s != '=')
	{
		if (!(ft_isalnum(*s) || *s == '_'))
		{
			write(2, "export: \'", 9);
			write(2, temp, ft_strlen(temp));
			write(2, "\'", 1);
			write(2, ": not a valid identifier\n", 25);
			return (1);
		}
		s++;
	}
	return (0);
}

int	only_name_add(char *argv, char ***env)
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(argv, (*env)[i], get_env_name_len((*env)[i])))
			return (0);
	}
	add_env(argv, env);
	return (0);
}

int	make_sort_hash(int *sort_hash, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		sort_hash[(int)(env[i][0])] = 1;
	return (0);
}
