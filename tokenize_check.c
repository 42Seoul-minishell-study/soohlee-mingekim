#include "minishell.h"

int	pipe_check(char ***token)
{
	if (token[0] == NULL)
		return (0);
	return (1);
}

int	operation_check(char ***token)
{
	int		i;
	char	*temp;

	i = 0;
	while (token[0][i] != NULL)
	{
		temp = find_next_word(token[0][i]);
		temp++;
		if (*temp == '<' || *temp == '>')
			return (0);
		i++;
	}
	return (1);
}

int	tokens_check(char *****tokens)
{
	int		index;

	index = 0;
	while ((*tokens)[index] != NULL)
	{
		if (pipe_check((*tokens)[index]) == 0)
		{
			free_tokens(tokens);
			write(2, "syntax error\n", 14);
			return (0);
		}
		if (operation_check((*tokens)[index]) == 0)
		{
			free_tokens(tokens);
			write(2, "syntax error\n", 14);
			return (0);
		}
		index++;
	}
	return (1);
}