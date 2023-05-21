/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:43:44 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/21 15:32:09 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_double_quate(char **out_str, int *offset, char **envp);
int cmd_line_expantions(char **out_one_line, char **envp);
int	cmd_basic_env_input(char **out_str, int *offset, char **envp);
int	cmd_single_quate(char **out_str, int *offset, char **envp);
int	cmd_double_quate(char **out_str, int *offset, char **envp);

// int	cmd_join(char **joined_cmd, char ***out_cmd);
// int cmd_line_expantions(char **out_joined_cmd, char **envp);
// int	cmd_single_quate(char **out_str, int *offset, char **envp);
// int	cmd_double_quate(char **out_str, int *offset, char **envp);

int	cmd_expansions(char ***out_cmd, char **envp)
{	
	int	cmd_num;

	printf("\ncmdexppaitn\n");
	cmd_num = -1;
	while ((*out_cmd)[++cmd_num])
		cmd_line_expantions(&((*out_cmd)[cmd_num]), envp);
	if (envp)
		;
	return (0);
}

int cmd_line_expantions(char **out_one_line, char **envp)
{
	int	offset;

	offset = -1;
	printf("onelone\n\n");
	while ((*out_one_line)[++offset])
	{
		printf("basic outoneline\n");
		if ((*out_one_line)[offset] == '\'')
			cmd_single_quate(out_one_line, &offset, envp);
		else if ((*out_one_line)[offset] == '\"')
			cmd_double_quate(out_one_line, &offset, envp);
		else if ((*out_one_line)[offset] == '$')
			cmd_basic_env_input(out_one_line, &offset, envp);
	}
	return (0);
}

int	cmd_basic_env_input(char **out_str, int *offset, char **envp)
{
	int		start;
	char	*env_str;
	char	*insert_str;
	char	*res;

	start = *offset;
	while((*out_str)[++(*offset)])
		if ((*out_str)[(*offset)] == '\''
			|| (*out_str)[(*offset)] == '\"'
				|| (*out_str)[(*offset)] == '$'
					|| (*out_str)[(*offset)] == ' ')
			break ;
	env_str = ft_substr(*out_str, start, *offset - start);
	if (!ft_strchr(env_str, '$'))
	{
		*offset = *offset - 1;
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
	printf("\nbaseic\n");
	return (0);
}

int	cmd_single_quate(char **out_str, int *offset, char **envp)	//하는중;
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
		return (0);
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

int	cmd_double_quate(char **out_str, int *offset, char **envp)
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
		return (0);
	insert_str = ft_substr(*out_str, start, *offset - start);
	temp = insert_str;
	insert_str = word_expanding(insert_str, envp);
	free(temp);
	temp = 0;
	res = ft_strinsert(*out_str, insert_str, start, *offset);
	free(*out_str);
	*out_str = res;
	*offset = start + ft_strlen(insert_str) - 1;
	if (envp)
		;
	return (0);
}