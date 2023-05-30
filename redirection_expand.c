/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:44:12 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 20:25:33 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_expand(char ***out_redir, char **envp)
{	
	int	redir_num;

	redir_num = -1;
	while ((*out_redir)[++redir_num])
		redir_line_expand(&((*out_redir)[redir_num]), envp);
	if (envp)
		;
	return (0);
}

int	redir_line_expand(char **out_one_line, char **envp)
{
	int		offset;
	char	*out_one_line_temp;

	offset = -1;
	while ((*out_one_line)[++offset])
	{
		if ((*out_one_line)[offset] == '\'')
			single_quate(out_one_line, &offset, envp);
		else if ((*out_one_line)[offset] == '\"')
			double_quate(out_one_line, &offset, envp);
		else if ((*out_one_line)[offset] == '$')
			redir_env_trans(out_one_line, &offset, envp);
	}
	out_one_line_temp = *out_one_line;
	*out_one_line = ft_strtrim(out_one_line_temp, " ");
	free(out_one_line_temp);
	out_one_line_temp = 0;
	return (0);
}

int	redir_env_trans(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*env_str;
	char	*insert_str;
	char	*res;

	start = *offset;
	while ((*out_str)[++(*offset)] == '$')
		;
	if ((*offset - start) > 1)
		return (0);
	(*offset)--;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\''
			|| (*out_str)[(*offset)] == '\"'
				|| (*out_str)[(*offset)] == '$'
					|| (*out_str)[(*offset)] == ' ')
			break ;
	if ((*offset - start) == 1)
		return (0);
	env_str = ft_substr(*out_str, start, *offset - start);
	if (!ft_strchr(env_str, '$') || !ft_strncmp(*out_str, "<<", 2))
	{
		(*offset)--;
		free(env_str);
		env_str = 0;
		return (0);
	}
	insert_str = getenv(env_str + 1);
	if (!insert_str)
		insert_str = ft_strdup("");
	insert_str = ft_strtrim(insert_str, " ");
	// ft_strchr로 공백있으면 리다이렉션 ambiguous redirect error처리 (ambigouso 후에도 나머지 파이프 정상작동)
	free(env_str);
	env_str = 0;
	res = ft_strinsert(*out_str, insert_str, start, *offset - 1);
	free(*out_str);
	*out_str = res;
	*offset = start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}
