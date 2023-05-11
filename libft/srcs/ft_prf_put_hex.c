/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prf_put_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:05:06 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:54 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	recursive_hex(unsigned int ap, char	*hex, int *prfcnt, int fd)
{
	if (ap > 15)
		recursive_hex(ap / 16, hex, prfcnt, fd);
	if (*prfcnt < 0)
		return (-1);
	if (ft_prf_putchar_fd(hex[ap % 16], fd, prfcnt) == -1)
	{
		*prfcnt = -1;
		return (-1);
	}
	return (*prfcnt);
}

int	ft_prf_put_hex(unsigned int ap, int *prfcnt, char format, int fd)
{
	char	*hex;

	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (recursive_hex(ap, hex, prfcnt, fd) == -1)
		return (-1);
	return (1);
}
