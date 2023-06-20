/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 16:23:00 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_export(char *argv, char ***env, int *idx);
int	is_unset_str(char *s);

int	ft_unset(char **argv, char ***env)
{
	int		i;
	char	**temp;
	int		flag;

	if (!argv || !argv[0])
		return (0);
	if (!(*(++argv)))
		return (0);
	g_exit_status = 0;
	temp = argv;
	flag = 0;
	while (*temp)
	{
		flag = flag + (is_unset_str(*temp));
		temp++;
	}
	i = -1;
	while (argv[++i])
		del_export(argv[i], env, &i);
	if (flag >= 1)
		g_exit_status = 1;
	return (0);
}

int	del_export(char *argv, char ***env, int *idx)
{
	char	*value;

	value = get_env(argv, *env);
	if (!value)
		free(value);
	else
	{
		free(value);
		delete_env(argv, env, 0);
		*idx = -1;
	}
	return (0);
}

int	is_unset_str(char *s)
{
	if (*s && ft_strchr(s, '='))
	{
		write(2, "unset: \'", 9);
		write(2, s, ft_strlen(s));
		write(2, "\'", 1);
		write(2, ": not a valid identifier\n", 25);
		return (1);
	}
	return (0);
}