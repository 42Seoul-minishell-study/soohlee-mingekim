/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:00:18 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 20:29:26 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *str, char *insert_str, int del_start, int del_len)
{
	char	*front_str;
	char	*end_str;
	char	*temp;
	char	*res;

	front_str = ft_substr(str, 0, del_start);
	end_str = ft_substr(str, del_len + 1, -1);
	temp = ft_strjoin(front_str, insert_str);
	res = ft_strjoin(temp, end_str);
	free(front_str);
	front_str = 0;
	free(end_str);
	end_str = 0;
	free(temp);
	temp = 0;
	return (res);
}
