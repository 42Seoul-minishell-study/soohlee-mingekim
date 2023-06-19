/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mi_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:00:18 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/19 14:31:16 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*mi_strinsert(char *str, char *insert_str, int del_start, int del_len)
{
	char	*front_str;
	char	*end_str;
	char	*temp;
	char	*res;

	front_str = ft_substr(str, 0, del_start);
	if (!front_str)
		exit (1);
	end_str = ft_substr(str, del_len + 1, -1);
	if (!end_str)
		exit (1);
	temp = ft_strjoin(front_str, insert_str);
	if (!temp)
		exit (1);
	res = ft_strjoin(temp, end_str);
	if (!res)
		exit (1);
	free(front_str);
	front_str = 0;
	free(end_str);
	end_str = 0;
	free(temp);
	temp = 0;
	return (res);
}
