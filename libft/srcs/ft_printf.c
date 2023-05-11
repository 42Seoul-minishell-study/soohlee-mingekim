/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:04:36 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:40 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_check(va_list ap, const char *arg, int *prfcnt)
{
	if (arg[0] == '%' && arg[1] == 'c')
		return (ft_prf_putchar_fd(va_arg(ap, int), 1, prfcnt));
	else if (arg[0] == '%' && arg[1] == 's')
		return (ft_prf_putstr_fd(va_arg(ap, char *), 1, prfcnt));
	else if (arg[0] == '%' && arg[1] == 'p')
		return (ft_prf_put_addrhex(va_arg(ap, void *), prfcnt, 1));
	else if (arg[0] == '%' && (arg[1] == 'd' || arg[1] == 'i'))
		return (ft_prf_putnbr_fd(va_arg(ap, int), 1, prfcnt));
	else if (arg[0] == '%' && (arg[1] == 'x' || arg[1] == 'X'))
		return (ft_prf_put_hex(va_arg(ap, unsigned int), prfcnt, arg[1], 1));
	else if (arg[0] == '%' && arg[1] == 'u')
		return (ft_prf_unsigned_putnbr_fd(va_arg(ap, unsigned int), 1, prfcnt));
	else if (arg[0] == '%' && arg[1] == '%')
		return (ft_prf_putchar_fd(arg[1], 1, prfcnt));
	else if (arg[0] == '%')
		return (-1);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *arg, ...)
{
	int		prfcnt;
	va_list	ap;
	int		i;
	int		temp;

	prfcnt = 0;
	va_start(ap, arg);
	i = 0;
	while (arg[i])
	{
		temp = print_check(ap, arg + i, &prfcnt);
		if (temp == -1)
			return (-1);
		else if (temp == 0)
		{
			if (ft_prf_putchar_fd(arg[i], 1, &prfcnt) == -1)
				return (-1);
		}
		else
			i++;
		i++;
	}
	va_end(ap);
	return (prfcnt);
}
