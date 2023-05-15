/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:25:31 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/15 17:15:40 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_expanding(char *out_double_str, char **envp) //""따옴표 포함한 문자열 받음
{
	char	*env_str;
	char	**split_env_str;

	env_str = ft_strtrim(out_double_str, "\"");
	if (!ft_strchr(out_double_str, '$'))
		return (env_str);
	split_env_str = ft_split (env_str, '$');
	free(env_str);
	env_str = 0;
	env_str = loop_expanding(split_env_str);
	if (envp)
		;
	return (env_str);
}

char	*loop_expanding(char **out_str)
{
	int		i;
	char	*small_word;
	char	*env_str;
	char	*temp;

	env_str = ft_strdup("");
	i = -1;
	while ((out_str)[++i])
	{
		printf("in%d\n", i);
		small_word = small_word_expanding((out_str)[i]);
		if (!small_word)
		{
			free(env_str);
			continue ;
		}
		printf("mi%d\n", i);
		temp = env_str;
		env_str = ft_strjoin(env_str, small_word);
		free(temp);
		temp = 0;
		free(small_word);
		small_word = 0;
		printf("out%d\n", i);
	}
	return (env_str);
}

char	*small_word_expanding(char *out_small_str)
{
	int		i;
	char	*temp_str;
	char	*env_value;
	char	*res_str;

	i = 0;
	printf("smmal: %s\n", out_small_str);
	while (out_small_str[i] && ft_isalnum(out_small_str[i]))
		i++;
	temp_str = ft_substr(out_small_str, 0, i);
	env_value = getenv(temp_str);
	if (!env_value)
		return (0);
	free(temp_str);
	temp_str = ft_substr(out_small_str, i, -1);
	printf("tempstr : %s\nenv_value: %s\n", temp_str, env_value);
	res_str = ft_strjoin(env_value, temp_str);
	free(env_value);
	free(temp_str);
	env_value = 0;
	temp_str = 0;
	return (res_str);
}

int	merge_word(char **out_str, char *out_middle_str, int start, int end)
{
	char	*temp_str;
	char	*front_and_back_str;
	char	*res_str;
	int		offset;

	front_and_back_str = ft_substr(*out_str, 0, start);
	res_str = ft_strjoin(front_and_back_str, out_middle_str);
	offset = ft_strlen(res_str);
	free(front_and_back_str);
	front_and_back_str = ft_substr(*out_str, end + 2, -1);
	temp_str = res_str;
	res_str = ft_strjoin(res_str, front_and_back_str);
	free(temp_str);
	temp_str = 0;
	free(*out_str);
	*out_str = res_str;
	return (offset);
}
