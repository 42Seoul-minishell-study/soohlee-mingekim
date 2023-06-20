/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:16:49 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 17:29:49 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env(char *new_str, char *del_name, char ***indepen_env)
{
	delete_env(del_name, indepen_env);
	add_env(new_str, indepen_env);
	return (0);
}

int	error_print(char *cmd, char *argv, char *messeage)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(messeage, 2);
	return (0);
}
