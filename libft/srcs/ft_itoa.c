/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:37:25 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:01:20 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mal_size(long long n)
{
	long long	cnt;

	if (n < 0)
	{
		n *= -1;
		cnt = 2;
	}
	else
		cnt = 1;
	while (n > 9)
	{
		n /= 10;
		cnt += 1;
	}
	return ((int)cnt + 1);
}

static void	trans_str(char *str, long long n, int i)
{
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	if (n > 9)
	{
		str[i] = n % 10 + '0';
		i--;
		trans_str(str, n / 10, i);
	}
	if (n < 10)
	{
		str[i] = n % 10 + '0';
		return ;
	}
	return ;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		mal_len;

	mal_len = mal_size((long long)n);
	str = (char *)malloc(sizeof(char) * mal_len);
	if (!str)
		return (0);
	str[mal_len - 1] = '\0';
	trans_str(str, (long long)n, mal_len - 2);
	return (str);
}
