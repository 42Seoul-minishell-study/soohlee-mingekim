/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:51:05 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 13:52:47 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_env_name_len(char *str)
{
	char	*temp;

	temp = str;
	while (*temp && *temp != '=')
		temp++;
	return (temp - str);
}

void	delete_env(char *env_name, char ***env_out)
{
	int		i;
	int		j;
	int		delete_index;
	char	**new_env;

	i = -1;
	while ((*env_out)[++i] != NULL)
	{
		if (ft_strncmp((*env_out)[i], env_name, \
			get_env_name_len((*env_out)[i])) == 0)
			delete_index = i;
	}
	new_env = malloc(sizeof(char *) * i);
	i = -1;
	j = 0;
	while ((*env_out)[++i] != NULL)
	{
		if (i == delete_index)
			continue ;
		new_env[j++] = (*env_out)[i];
	}
	new_env[j] = NULL;
	free(*env_out);
	*env_out = new_env;
}

void	free_env(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		free((*env)[i]);
		i++;
	}
	free((*env));
	*env = NULL;
}

char	*get_env(char *env_name, char **env)
{
	int		i;
	int		find_index;
	char	*temp;
	char	*str_env;

	i = -1;
	find_index = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], env_name, get_env_name_len(env[i])) == 0 && \
			ft_strlen(env_name) == get_env_name_len(env[i]))
			find_index = i;
	}
	if (find_index == -1)
		return (NULL);
	temp = ft_strchr(env[find_index], '=');
	if (!temp)
		return (ft_strdup(""));
	++temp;
	str_env = ft_strdup(temp);
	return (str_env);
}
