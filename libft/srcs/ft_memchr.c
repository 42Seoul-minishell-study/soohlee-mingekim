/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:11:32 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:01:10 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;
	unsigned char	c1;

	c1 = (unsigned char)c;
	cs = (unsigned char *)s;
	i = 0;
	if (!n)
		return (0);
	while (n > 0)
	{
		if (cs[i] == c1)
			return ((void *)(cs + i));
		n--;
		i++;
	}
	return (0);
}
