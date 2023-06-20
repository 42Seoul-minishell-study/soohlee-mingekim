/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:51:05 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 17:19:10 by soohlee          ###   ########.fr       */
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

void	delete_env(char *env_name, char ***env, int delete_index)
{
	int		index[3];
	char	**new_env;

	index[0] = -1;
	if (is_compare(env_name, *env))
		return ;
	while ((*env)[++index[0]] != NULL)
	{
		if (ft_strncmp((*env)[index[0]], env_name, \
			get_env_name_len((*env)[index[0]])) == 0)
			delete_index = index[0];
	}
	new_env = malloc(sizeof(char *) * ft_twod_strlen(*env));
	if (new_env == NULL)
		perror_and_exit("malloc", 1);
	index[0] = -1;
	index[1] = 0;
	while ((*env)[++index[0]] != NULL)
	{
		if (index[0] != delete_index)
			new_env[index[1]++] = ft_strdup((*env)[index[0]]);
	}
	new_env[index[1]] = NULL;
	free_env(env);
	*env = new_env;
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
		return (mi_strdup(""));
	++temp;
	str_env = mi_strdup(temp);
	return (str_env);
}

int	ft_twod_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
