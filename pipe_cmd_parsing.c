/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:17 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/20 20:29:17 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all_cmd_str(char **command_split)
{
	char	**temp;

	temp = command_split;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(command_split);
}

static int	free_and_exit(char **envp_split, char *command)
{
	if (envp_split != NULL)
		free_all_cmd_str(envp_split);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 21);
	exit(127);
}

static char	*join_path(char *envp_path, char *command)
{
	char	*temp;
	char	*command_path;

	temp = mi_strjoin(envp_path, "/");
	command_path = mi_strjoin(temp, command);
	free(temp);
	return (command_path);
}

static char	**parsing_path_or_null(char **envp)
{
	char	*path;

	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			break ;
		envp++;
	}
	if (*envp == NULL)
		return (NULL);
	if (ft_strncmp("PATH=", *envp, 5) == 0)
	{
		path = *envp + 5;
		return (ft_split(path, ':'));
	}
	return (NULL);
}

void	parsing_cmd_and_options(char **command, char **envp, int envp_index)
{
	char	*result;
	char	**envp_split;

	envp_index = 0;
	result = command[0];
	if (is_builtin(command) == 1)
		return ;
	if (access(command[0], X_OK) == 0 || ft_strchr(command[0], '/') != NULL)
		return ;
	envp_split = parsing_path_or_null(envp);
	if (envp_split == NULL)
		perror_and_exit(result, 127);
	while (envp_split[envp_index] != NULL)
	{
		result = join_path(envp_split[envp_index++], command[0]);
		if (access(result, X_OK) == 0)
		{
			free(command[0]);
			command[0] = result;
			free_all_cmd_str(envp_split);
			return ;
		}
		free(result);
	}
	free_and_exit(envp_split, command[0]);
}
