/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:46 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/01 15:09:42 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_export(char *argv, char ***env);
int	print_export(char **env);
int	is_export_str(char *s);

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

	if (!ft_strchr(argv, '='))
		return (0);
	name = ft_substr(argv, 0, ft_strchr(argv, '=') - argv);
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
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
		{
			write(1, &(env[i][j]), 1);
			if (env[i][j] == '=')
				write(1, "\"", 1);
		}
		write(1, "\"\n", 2);
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
