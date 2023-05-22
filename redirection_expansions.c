/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:44:12 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/22 18:40:56 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_expansions(char ***out_redir, char **envp)
{	
	int	redir_num;

	redir_num = -1;
	while ((*out_redir)[++redir_num])
		redir_line_expantions(&((*out_redir)[redir_num]), envp);
	if (envp)
		;
	return (0);
}

int	redir_line_expantions(char **out_one_line, char **envp)
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
			env_input(out_one_line, &offset, envp);
	}
	out_one_line_temp = *out_one_line;
	*out_one_line = ft_strtrim(out_one_line_temp, " ");
	free(out_one_line_temp);
	out_one_line_temp = 0;
	return (0);
}

int	env_input(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*env_str;
	char	*insert_str;
	char	*res;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\''
			|| (*out_str)[(*offset)] == '\"'
				|| (*out_str)[(*offset)] == '$'
					|| (*out_str)[(*offset)] == ' ')
			break ;
	env_str = ft_substr(*out_str, start, *offset - start);
	if (!ft_strchr(env_str, '$'))
	{
		(*offset)--;
		free(env_str);
		env_str = 0;
		return (0);
	}
	insert_str = getenv(env_str + 1);
	if (!insert_str)
		insert_str = "";
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

int	single_quate(char **out_str, int *offset, char **envp)	//하는중;
{
	int		start;
	char	*insert_str;
	char	*res;
	char	*temp;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\'')
			break ;
	if (!(*out_str)[(*offset)])
	{
		*offset = start;
		return (0);
	}
	insert_str = ft_substr(*out_str, start, *offset - start);
	temp = insert_str;
	insert_str = ft_strtrim(insert_str, "\'");
	free(temp);
	temp = 0;
	res = ft_strinsert(*out_str, insert_str, start, *offset);
	free(*out_str);
	*out_str = res;
	*offset = start + *offset - start - 2;
	if (envp)
		;
	return (0);
}

int	double_quate(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*insert_str;
	char	*res;
	char	*temp;

	start = *offset;
	while ((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\"')
			break ;
	if (!(*out_str)[(*offset)])
	{
		*offset = start;
		return (0);
	}
	insert_str = ft_substr(*out_str, start, (*offset + 1) - start);
	temp = insert_str;
	insert_str = ft_strtrim(temp, "\"");
	free(temp);
	word_expanding(&insert_str, envp);
	res = ft_strinsert(*out_str, insert_str, start, *offset);
	free(*out_str);
	*out_str = res;
	*offset = start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}
