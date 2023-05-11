/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:30:43 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:30 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	dst_len_fix;
	size_t	src_len;
	size_t	src_index;
	size_t	dst_plus_src;

	src_index = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	dst_plus_src = dst_len + src_len;
	if (dst_len > dstsize)
		return (src_len + dstsize);
	dst_len_fix = dst_len;
	while (dstsize > dst_len_fix + 1 && src[src_index])
	{
		dst[dst_len] = src[src_index];
		dstsize--;
		src_index++;
		dst_len++;
	}
	dst[dst_len] = 0;
	return (dst_plus_src);
}
