/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:49:22 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:27 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(unsigned char *str, unsigned char *to_find, size_t l)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] == to_find[j] && to_find[j] && l--)
	{
		j++;
		i++;
	}
	if (to_find[j] == 0)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)haystack;
	s2 = (unsigned char *)needle;
	i = 0;
	if (s2[i] == 0)
		return ((char *)haystack);
	while (len && s1[i])
	{
		{
			if (check(&s1[i], s2, len) == 1)
				return ((char *)&s1[i]);
			i++;
		}
		len--;
	}
	return (0);
}
