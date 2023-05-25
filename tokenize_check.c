#include "minishell.h"

int	pipe_check(char ***token)
{
	if (token[0] == NULL)
		return (0);
	return (1);
}

int	operation_check(char ***token)
{
	int	index;

	
	return (1);
}

int	tokens_check(char *****tokens)
{
	int		index;

	index = 0;
	while (tokens[index] != NULL)
	{
		if (pipe_check(tokens[index]) == 0)
		{
			//free_all
			//print syntax error
			//exit
		}
		if (operation_check(tokens[index]) == 0)
		{
			//free_all
			//print syntax error
			//exit
		}
		index++;
	}
	

	return (1);
}