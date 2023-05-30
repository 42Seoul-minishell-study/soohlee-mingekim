/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:17 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:25 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *envp_path, char *command)
{
	char	*temp;
	char	*command_path;

	temp = ft_strjoin(envp_path, "/");
	command_path = ft_strjoin(temp, command);
	free(temp);
	return (command_path);
}

char	**parsing_path_or_null(char **envp)
{
	char	*path;

	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			break ;
		envp++;
	}
	if (ft_strncmp("PATH=", *envp, 5) == 0)
	{
		path = *envp + 5;
		return (ft_split(path, ':'));
	}
	return (NULL);
}

void	free_all_cmd_str(char **command_split)
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

static int	free_and_error(char **envp_split, char *command)
{
	free_all_cmd_str(envp_split);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 21);
	return (0);
}

int	parsing_cmd_and_options(char **command_out, char **envp)
{
	int		envp_index;
	char	*result;
	char	**envp_split;

	envp_index = 0;
	result = command_out[0];
	if (access(command_out[0], X_OK) == 0)
		return (1);
	envp_split = parsing_path_or_null(envp);
	while (envp_split[envp_index] != NULL)
	{
		result = join_path(envp_split[envp_index++], command_out[0]);
		if (access(result, X_OK) == 0)
		{
			free(command_out[0]);
			command_out[0] = result;
			free_all_cmd_str(envp_split);
			return (1);
		}
		free(result);
	}
	return (free_and_error(envp_split, command_out[0]));
}