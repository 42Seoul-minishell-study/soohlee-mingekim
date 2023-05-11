/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:33:56 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/06 02:00:34 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	double_malcnt(char *s, char c)
{
	size_t	cnt;
	size_t	flag;
	size_t	i;

	flag = 0;
	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			cnt++;
			flag = 1;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (cnt);
}

static size_t	wordlen(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*wordcpy(char *s1, char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (len)
	{
		s1[i] = s2[i];
		i++;
		len--;
	}
	s1[i] = 0;
	return (s2);
}

static void	frmal(char **s, size_t i)
{
	if (i != 0)
	{
		i -= 1;
		while (i)
		{
			free(s[i]);
			i--;
		}
		free (s[i]);
	}
	free (s);
}

char	**ft_split(char const *s, char c)
{
	char	**new_s;
	size_t	word;
	size_t	i;

	i = 0;
	new_s = (char **)malloc(sizeof(char *) * (double_malcnt((char *)s, c) + 1));
	if (!new_s)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		word = wordlen((char *)s, c);
		new_s[i] = (char *)malloc(sizeof(char) * (word + 1));
		if (!new_s[i])
		{
			frmal(new_s, i);
			return (0);
		}
		s = word + wordcpy(new_s[i++], (char *)s, word);
	}
	new_s[i] = 0;
	return (new_s);
}
