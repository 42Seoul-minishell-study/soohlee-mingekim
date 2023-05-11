/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:11:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:33 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s1;
	char	c1;

	s1 = (char *)s;
	c1 = (char)c;
	i = 0;
	while (s1[i])
	{
		if (s1[i] == c1)
			return ((char *)s1 + i);
		i++;
	}
	if (c1 == 0)
		return ((char *)s1 + i);
	else
		return (0);
}
