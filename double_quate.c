/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:25:31 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/22 18:20:10 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_expanding(char **out_str, char **envp)
{
	int	offset;

	offset = -1;
	while ((*out_str)[++offset])
	{
		if ((*out_str)[offset] == '$')
			env_input(out_str, &offset, envp);
	}
	return (0);
}
