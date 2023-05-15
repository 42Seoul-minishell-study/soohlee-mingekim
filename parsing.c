/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:53:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/15 16:19:25 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char **out_str, char ****out_data, char **envp)
{
	expanding(out_str, envp);
	printf("expanded :%s\n", *out_str);
//	redirections_merge(out_str);
//	split_simple_command(out_str, out_data);
	if (out_data)
		;
	return (0);
}
