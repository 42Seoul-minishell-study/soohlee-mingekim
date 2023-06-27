/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:46:27 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/27 11:52:32 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	atoi_check(const char *str)
{
	int					i;
	unsigned long long	res;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10);
		res = res + (str[i] - '0');
		i++;
	}
	return (res);
}

static const char	*str_check(const char *str)
{
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	k;
	int	flag;

	flag = 0;
	k = 1;
	i = 0;
	str = (const char *)str_check(str);
	while (!(str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			return ((int)(k * atoi_check(&str[i])));
		if (!(str[i] == '-' || str[i] == '+'))
			return (0);
		if (str[i] == '-' || str[i] == '+')
			flag++;
		if (flag > 1)
			return (0);
		if (str[i] == '-')
			k *= -1;
		i++;
	}
	return (0);
}
