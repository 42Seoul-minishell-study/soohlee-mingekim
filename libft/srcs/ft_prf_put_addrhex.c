/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prf_put_addrhex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:05:06 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:57 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	recursive_hex(size_t ap_addr, char	*hex, int *prfcnt, int fd)
{
	if (ap_addr > 15)
		recursive_hex(ap_addr / 16, hex, prfcnt, fd);
	if (*prfcnt < 0)
		return (-1);
	if (ft_prf_putchar_fd(hex[ap_addr % 16], fd, prfcnt) == -1)
	{
		*prfcnt = -1;
		return (-1);
	}
	return (1);
}

int	ft_prf_put_addrhex(void *ap, int *printfcnt, int fd)
{
	size_t	ap_addr;
	char	*hex;

	hex = "0123456789abcdef";
	ap_addr = (size_t)ap;
	if (ft_prf_putstr_fd("0x", 1, printfcnt) == -1)
		return (-1);
	if (recursive_hex(ap_addr, hex, printfcnt, fd) == -1)
		return (-1);
	return (1);
}
