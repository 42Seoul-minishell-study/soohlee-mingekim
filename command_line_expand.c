
#include "minishell.h"

static char	*malloc_and_reset(void)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * 2);
	if (result == NULL)
		perror_and_exit("malloc", 1);
	result[0] = ' ';
	result[1] = '\0';
	return (result);
}

static char	*join_with_param(char *result, char *param)
{
	char	*temp;

	if (param == NULL)
		return (result);
	temp = mi_strjoin(result, param);
	free(result);
	free(param);
	return (temp);
}

char	*line_expand_1(char *cmd, char **env)
{
	char	*last;
	char	*result;

	result = malloc_and_reset();
	while (*cmd != '\0')
	{
		if (*cmd == '\'')
		{
			last = find_next_single_quote(cmd);
			result = join_with_param(result, dup_with_len(cmd, last));
			cmd = last;
		}
		if (*cmd == '\"')
		{
			last = find_next_double_quote(cmd);
			result = join_with_param(result, dup_with_len(cmd, last));
			cmd = last;
		}
		if (*cmd == '$')
		{
			last = find_last(++cmd, 1);
			result = join_with_param(result, get_env_name(cmd, last, env));
			cmd = last;
		}
		else
		{
			last = find_last(cmd, 0);
			result = join_with_param(result, dup_with_len(cmd, last));
			cmd = last;
		}
	}
	return (result);
}

static int	redir_env_trans(char **tokens, int *start, int *offset, char **env)
{
	char	*insert_str;
	char	*temp;
	char	*env_str;

	env_str = mi_substr(*tokens, *start, *offset - *start);
	if (!env_str)
		exit (1);
	insert_str = get_env(env_str + 1, env);
	if (!insert_str)
		insert_str = mi_strdup("");
	one_d_free_null(&env_str);
	temp = insert_str;
	insert_str = mi_strtrim(temp, " ");
	one_d_free_null(&temp);
	temp = *tokens;
	*tokens = mi_strinsert(temp, insert_str, *start, *offset - 1);
	one_d_free_null(&temp);
	*offset = *start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

static int	single_quote_expand(char **tokens, int *offset)
{
	int		start;
	char	*insert_str;
	char	*temp;

	start = *offset;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\'')
			break ;
	if (!(*tokens)[(*offset)])
	{
		*offset = start;
		return (0);
	}
	insert_str = mi_substr(*tokens, start, (*offset + 1) - start);
	temp = insert_str;
	insert_str = mi_strtrim(temp, "\'");
	one_d_free_null(&temp);
	temp = mi_strinsert(*tokens, insert_str, start, *offset);
	free(*tokens);
	*tokens = temp;
	temp = 0;
	*offset = start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

static int	double_quote_expand(char **tokens, int *offset, char **env)
{
	int		start;
	char	*insert_str;
	char	*temp;

	start = *offset;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\"')
			break ;
	if (!(*tokens)[(*offset)])
	{
		*offset = start;
		return (0);
	}
	insert_str = mi_substr(*tokens, start, (*offset + 1) - start);
	temp = insert_str;
	insert_str = mi_strtrim(temp, "\"");
	one_d_free_null(&temp);
	word_expand(&insert_str, env);
	temp = mi_strinsert(*tokens, insert_str, start, *offset);
	free(*tokens);
	*tokens = temp;
	*offset = start + ft_strlen(insert_str) - 1;
	one_d_free_null(&insert_str);
	return (0);
}

static int	redir_env_check(char **tokens, int *offset, char **env)
{
	int		start;
	char	*env_str;

	start = *offset;
	while ((*tokens)[++(*offset)] == '$')
		;
	if ((*offset - start) > 1)
		return (0);
	(*offset)--;
	while ((*tokens)[++(*offset)])
		if ((*tokens)[(*offset)] == '\''
			|| (*tokens)[(*offset)] == '\"'
				|| (*tokens)[(*offset)] == '$'
					|| (*tokens)[(*offset)] == ' ')
			break ;
	if ((*offset - start) == 1)
		return (0);
	env_str = mi_substr(*tokens, start, *offset - start);
	if (!ft_strchr(env_str, '$'))
		return ((one_d_free_null(&env_str) + (*offset)--) * 0);
	one_d_free_null(&env_str);
	return (redir_env_trans(tokens, &start, offset, env));
}

void	in_quote_expand(char **cmd, char **env)
{
	int		offset;
	char	*tokens_temp;

	offset = -1;
	while ((*cmd)[++offset])
	{
		if ((*cmd)[offset] == '\'')
			single_quote_expand(cmd, &offset);
		else if ((*cmd)[offset] == '\"')
			double_quote_expand(cmd, &offset, env);
	}
	tokens_temp = *cmd;
	*cmd = mi_strtrim(tokens_temp, " ");
	free(tokens_temp);
	tokens_temp = 0;
}

void	line_expand(char **cmd, char **env)
{
	int		offset;
	char	*tokens_temp;

	offset = -1;
	while ((*cmd)[++offset])
	{
		if ((*cmd)[offset] == '\'')
			single_quote_expand(cmd, &offset);
		else if ((*cmd)[offset] == '\"')
			double_quote_expand(cmd, &offset, env);
		else if ((*cmd)[offset] == '$')
			redir_env_check(cmd, &offset, env);
	}
	tokens_temp = *cmd;
	*cmd = mi_strtrim(tokens_temp, " ");
	free(tokens_temp);
	tokens_temp = 0;
}
