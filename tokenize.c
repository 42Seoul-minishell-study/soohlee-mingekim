#include "minishell.h"

static int	get_pipe_count(char *str)
{
	int	count;

	count = 0;
	str = find_next_pipe(str);
	while (*str != '\0')
	{
		count++;
		str = find_next_pipe(str);
	}
	return (count);
}

static char	***split_tokens(char *str)
{
	int		index;
	char	***ops_and_words;

	index = 0;
	ops_and_words = malloc(sizeof(char **) * 3);
	if (ops_and_words == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	set_ops_and_words(str, ops_and_words);
	ops_and_words[2] = NULL;
	return (ops_and_words);
}

void	print_all_tree(char ****tokens)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (tokens[i] != NULL)
	{
		j = 0;
		while (tokens[i][j] != NULL)
		{
			k = 0;
			while (tokens[i][j][k] != NULL)
			{
				printf("%d %d %d: %s\n", i, j, k, tokens[i][j][k]);
				k++;
			}
			j++;
		}
		i++;
	}
}

char	****tokenize(char *str)
{
	int		index;
	int		tokens_len;
	char	****tokens;

	index = 0;
	tokens_len = get_pipe_count(str) + 1;
	tokens = malloc(sizeof(char ***) * (tokens_len + 1));
	if (tokens == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	tokens[index++] = split_tokens(str);
	while (index < tokens_len)
	{
		str = find_next_pipe(str);
		tokens[index] = split_tokens(str);
		if (tokens[index] == NULL)
			return (free_tokens(&tokens));
		index++;
	}
	tokens[tokens_len] = NULL;
	print_all_tree(tokens);
	return (tokens);
}