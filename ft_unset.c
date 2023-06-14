/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 20:08:10 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_export(char *argv, char ***env, int *idx);

int	ft_unset(char **argv, char ***env)
{
	int	i;

	if (!argv || !argv[0])
		return (0);
	if (!(*(++argv)))
		return (0);
	i = -1;
	while (argv[++i])
		del_export(argv[i], env, &i);
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
		delete_env(argv, env);
		*idx = -1;
	}
	return (0);
}
