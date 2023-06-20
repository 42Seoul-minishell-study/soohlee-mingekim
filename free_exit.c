/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:25:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/20 20:12:41 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	two_d_free_null(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = 0;
		i++;
	}
	free(*str);
	str = 0;
	return (0);
}

int	one_d_free_null(char **str)
{
	free(*str);
	*str = 0;
	return (0);
}
