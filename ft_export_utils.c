/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:18:32 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/22 13:52:43 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_sort_hash(int *sort_hash, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		sort_hash[(int)(env[i][0])] = 1;
	return (0);
}

int	only_name_add(char *argv, char ***env)
{
	int	i;
	int	newenv_len;

	newenv_len = ft_strlen(argv);
	i = -1;
	while ((*env)[++i])
	{
		if ((int)ft_strlen((*env)[i]) >= newenv_len && \
			!ft_strncmp(argv, (*env)[i], (int)newenv_len))
			return (0);
	}
	add_env(argv, env);
	return (0);
}

int	print_export_oneline(char **env, int *i, int *j)
{
	while (env[*i][++(*j)])
	{
		write(1, &(env[*i][*j]), 1);
		if (env[*i][*j] == '=')
			write(1, "\"", 1);
	}
	if (ft_strchr(env[*i], '='))
		write(1, "\"\n", 2);
	else
		write(1, "\n", 1);
	return (0);
}
