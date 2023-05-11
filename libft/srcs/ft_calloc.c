/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:56:09 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 01:49:07 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	size_t	over_flow_check;

	over_flow_check = 0;
	if (count != 0 && size != 0)
	{
		over_flow_check = count * size;
		if ((over_flow_check / size) != count)
			return (0);
	}
	temp = malloc(over_flow_check);
	if (!temp)
		return (0);
	ft_bzero (temp, over_flow_check);
	return (temp);
}
