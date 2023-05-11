/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prf_putnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:48:53 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:53 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c, int fd, int *prfcnt)
{
	if (write (fd, &c, 1) == -1)
		return (-1);
	*prfcnt += 1;
	return (1);
}

static int	printnbr(long long bnb, int fd, int *prfcnt)
{
	if (bnb >= 10)
		printnbr (bnb / 10, fd, prfcnt);
	if (*prfcnt < 0)
		return (-1);
	if (ft_putchar ((bnb % 10) + '0', fd, prfcnt) == -1)
	{
		*prfcnt = -1;
		return (-1);
	}
	return (1);
}

int	ft_prf_putnbr_fd(int n, int fd, int *prfcnt)
{
	long long	bnb;

	bnb = n;
	if (bnb >= 0)
	{
		if (printnbr(bnb, fd, prfcnt) == -1)
			return (-1);
	}
	else if (bnb < 0)
	{
		*prfcnt += 1;
		if (write (fd, "-", 1) == -1)
			return (-1);
		if (printnbr(-bnb, fd, prfcnt) == -1)
			return (-1);
	}
	return (1);
}
