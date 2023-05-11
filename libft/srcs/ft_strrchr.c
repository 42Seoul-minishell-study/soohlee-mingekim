/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:13:23 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:25 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long long		i;
	unsigned char	c1;

	c1 = (unsigned char)c;
	i = ft_strlen(s);
	while (i)
	{
		if (s[i] == c1)
			return ((char *)(s + i));
		i--;
	}
	if (s[i] == c1)
		return ((char *)(s + i));
	return (0);
}
