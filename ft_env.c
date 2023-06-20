/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:59:06 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 13:04:34 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1 + is_compare("OLDPWD", envp)));
	i = 0;
	while (envp[i] != NULL)
	{
		if ((ft_strlen(envp[i]) >= 6) && (!ft_strncmp(envp[i], "OLDPWD", 6)) \
			&& (envp[i][6] == '\0' || envp[i][6] == '=' ))
		{
			env[i] = mi_strdup("OLDPWD");
			i++;
		}
		else
		{
			env[i] = mi_strdup(envp[i]);
			i++;
		}
	}
	if (is_compare("OLDPWD", envp) == 1)
		env[i++] = mi_strdup("OLDPWD");
	env[i] = NULL;
	return (env);
}

void	add_env(char *new_str, char ***env_out)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env_out)[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (++i + 1));
	i = 0;
	while ((*env_out)[i] != NULL)
	{
		new_env[i] = (*env_out)[i];
		i++;
	}
	new_env[i++] = mi_strdup(new_str);
	if (!new_env[i - 1])
		exit (1);
	new_env[i] = NULL;
	free(*env_out);
	*env_out = new_env;
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}

void	ft_env(char **env)
{
	print_env(env);
	g_exit_status = 0;
}

int	is_compare(char *compare, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], compare, ft_strlen(compare)) == 0)
			return (0);
	}
	return (1);
}
