/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:33:56 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/21 16:26:06 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	double_m_malcnt(char *s, char c1, char c2)
{
	size_t	cnt;
	size_t	flag;
	size_t	i;

	flag = 0;
	i = 0;
	cnt = 0;
	while (s[i])
	{
		if ((s[i] != c1 && flag == 0) || (s[i] != c2 && flag == 0))
		{
			cnt++;
			flag = 1;
		}
		else if ((s[i] == c1) || (s[i] == c2))
			flag = 0;
		i++;
	}
	return (cnt);
}

static size_t	m_wordlen(char *s, char c1, char c2)
{
	size_t	i;

	i = 0;
	while ((s[i] && s[i] != c1) || (s[i] && s[i] != c2))
		i++;
	return (i);
}

static char	*m_wordcpy(char *s1, char *s2, size_t len)
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

static void	m_frmal(char **s, size_t i)
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

char	**ft_m_split(char const *s, char c1, char c2)
{
	char	**new_s;
	size_t	word;
	size_t	i;

	i = 0;
	new_s = (char **)malloc(sizeof(char *) * \
		(double_m_malcnt((char *)s, c1, c2) + 1));
	if (!new_s)
		return (0);
	while (*s)
	{
		while ((*s && *s == c1) || (*s && *s == c2))
			s++;
		if (!*s)
			break ;
		word = m_wordlen((char *)s, c1, c2);
		new_s[i] = (char *)malloc(sizeof(char) * (word + 1));
		if (!new_s[i])
		{
			m_frmal(new_s, i);
			return (0);
		}
		s = word + m_wordcpy(new_s[i++], (char *)s, word);
	}
	new_s[i] = 0;
	return (new_s);
}
