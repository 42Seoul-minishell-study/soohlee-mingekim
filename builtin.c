/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:10:00 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/18 15:10:01 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(char **cmd, char ***env)
{
	if (cmd[0] == NULL)
		return ;
	if (ft_strlen(cmd[0]) == 2 && !ft_strncmp(cmd[0], "cd", 3))
		ft_cd(cmd, env);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd();
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "env", 4))
		ft_env(*env);
	else if (ft_strlen(cmd[0]) == 6 && !ft_strncmp(cmd[0], "export", 7))
		ft_export(cmd, env);
	else if (ft_strlen(cmd[0]) == 5 && !ft_strncmp(cmd[0], "unset", 6))
		ft_unset(cmd, env);
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd, env);
}

int	is_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (ft_strlen(cmd[0]) == 2 && !ft_strncmp(cmd[0], "cd", 3))
		return (1);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "pwd", 4))
		return (1);
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "echo", 5))
		return (1);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "env", 4))
		return (1);
	else if (ft_strlen(cmd[0]) == 6 && !ft_strncmp(cmd[0], "export", 7))
		return (1);
	else if (ft_strlen(cmd[0]) == 5 && !ft_strncmp(cmd[0], "unset", 6))
		return (1);
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "exit", 5))
		return (1);
	return (0);
}