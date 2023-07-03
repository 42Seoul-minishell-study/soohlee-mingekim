/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:42 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 20:32:32 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	translation(char *****tokens, char **envp)
{
	if (*tokens == NULL)
		return (0);
	shell_expand(tokens, envp);
	return (0);
}
