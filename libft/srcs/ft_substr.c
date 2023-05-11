/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:03:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:24 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*m1;
	size_t	i;
	size_t	after_len;

	i = 0;
	if ((ft_strlen((s)) < start) || s == 0)
		return (ft_strdup(""));
	after_len = ft_strlen(s + start);
	if (after_len < len)
		len = after_len;
	s = s + start;
	m1 = (char *)malloc(sizeof(char) * len + 1);
	if (m1 == 0)
		return (0);
	while (i < len && i < after_len)
	{
		m1[i] = s[i];
		i++;
	}
	m1[i] = 0;
	return (m1);
}
