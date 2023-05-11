/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:48:53 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:38 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write (fd, &c, 1);
}

static void	printnbr(long long bnb, int fd)
{
	if (bnb >= 10)
		printnbr (bnb / 10, fd);
	ft_putchar ((bnb % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	bnb;

	bnb = n;
	if (bnb >= 0)
		printnbr(bnb, fd);
	else if (bnb < 0)
	{
		write (fd, "-", 1);
		printnbr(-bnb, fd);
	}
}
