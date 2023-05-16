#include "minishell.h"

char	*find_next_pipe(char *str)
{
	while (*str != '\0' && *str != '|')
	{
		if (ft_strncmp(str, "\'", 1) == 0)
		{
			str = find_next_single_quote(str);
		}
		else if (ft_strncmp(str, "\"", 1) == 0)
		{
			str = find_next_double_quote(str);
		}
		str++;
	}
	return (str);
}

char	*find_next_word(char *str)
{
	while (*str != '\0' && *str != ' ')
	{
		if (ft_strncmp(str, "\'", 1) == 0)
		{
			str = find_next_single_quote(str);
		}
		else if (ft_strncmp(str, "\"", 1) == 0)
		{
			str = find_next_double_quote(str);
		}
		str++;
	}
	return (str);
}

char	*pass_space(char *str)
{
	while (*str != '\0' && *str == ' ')
	{
		str++;
	}
	return (str);
}

int	get_pipe_count(char *str)
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

void	get_words_and_ops_count(char *str, int *ops_count_out, int *words_count_out)
{
	*ops_count_out = 0;
	*words_count_out = 0;
	while (*str != '\0' && *str != '|')
	{
		if (ft_strncmp(str, "<<", 2) == 0)
		{
			str += 2;
			str = pass_space(str);
			str = find_next_word(str);
			*ops_count_out++;
		}
		else if (ft_strncmp(str, "<", 1) == 0)
		{
			str += 1;
			str = pass_space(str);
			str = find_next_word(str);
			*ops_count_out++;
		}
		else if (ft_strncmp(str, ">>", 2) == 0)
		{
			str += 2;
			str = pass_space(str);
			str = find_next_word(str);
			*ops_count_out++;
		}
		else if (ft_strncmp(str, ">", 1) == 0)
		{
			str += 1;
			str = pass_space(str);
			str = find_next_word(str);
			*ops_count_out++;
		}
		else
		{
			str = pass_space(str);
			str = find_next_word(str);
			*words_count_out++;
		}
	}
}

int	is_redirection(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(str, "<", 1) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(str, ">>", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(str, ">", 1) == 0)
	{
		return (1);
	}
	return (0);
}

char	*split_ops(char *str, char **op_out)
{
	int		len_op;
	int		len_filename;
	char	*temp;
	char	*filename;
	char	*result;

	temp = str;
	len_op = 1;
	if (ft_strncmp(str, "<<", 2) == 0)
	{
		temp += 2;
		len_op += 2;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	else if (ft_strncmp(str, "<", 1) == 0)
	{
		temp += 1;
		len_op += 1;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	else if (ft_strncmp(str, ">>", 2) == 0)
	{
		temp += 2;
		len_op += 2;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	else if (ft_strncmp(str, ">", 1) == 0)
	{
		temp += 1;
		len_op += 1;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	*op_out = malloc(sizeof(char) * (len_op + len_filename + 1));
	if (*op_out == NULL)
	{
		perror("malloc");
		return (str);
	}
	ft_memcpy(*op_out, str, len_op);
	(*op_out)[len_op] = ' ';
	ft_memcpy(*op_out + len_op, filename, len_filename);
	(*op_out)[len_op + len_filename] = 0;
	return (temp);
}

char	*split_words(char *str, char **word_out)
{
	int		len;
	char	*temp;

	temp = find_next_word(str);
	len = temp - str;
	*word_out = malloc(sizeof(char) * (len + 1));
	ft_memcpy(*word_out, str, len);
	(*word_out)[len] = 0;
	return (temp);
}

char	***split_tokens(char *str)
{
	int		index;
	int		index_word;
	int		index_op;
	int		words_count;
	int		ops_count;
	char	***ops_and_words;

	index = 0;
	index_word = 0;
	index_op = 0;
	ops_and_words = malloc(sizeof(char **) * 2);
	if (ops_and_words == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	get_words_and_ops_count(str, &ops_count, &words_count);
	ops_and_words[0] = malloc(sizeof(char *) * (ops_count + 1));
	if (ops_and_words[0] == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	ops_and_words[1] = malloc(sizeof(char *) * (words_count + 1));
	if (ops_and_words[1] == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while (*str != '\0' && *str != '|')
	{
		pass_space(str);
		if (is_redirection(str) == 1)
		{
			str = split_ops(str, &ops_and_words[0][index_op]);
			if (ops_and_words[0][index_op] == NULL)
			{
				//freeall
				return (NULL);
			}
			index_op++;
		}
		else
		{
			str = split_words(str, &ops_and_words[1][index_word]);
			if (ops_and_words[0][index_word] == NULL)
			{
				//freeall
				return (NULL);
			}
			index_word++;
		}
	}
	return (ops_and_words);
}

char	****tokenize(char *str)
{
	int		offset;
	int		index;
	int		tokens_len;
	char	*temp;
	char	****tokens;

	index = 0;
	temp = str;
	tokens_len = get_pipe_count(str) + 1;
	tokens = malloc(sizeof(char ***) * (tokens_len + 1));
	if (tokens == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	temp = find_next_pipe(temp);
	tokens[index++] = split_tokens(str);
	while (index < tokens_len)
	{
		temp = find_next_pipe(temp);
		tokens[index] = split_tokens(str);
		if (tokens[index] == NULL)
			return (free_tokens(&tokens));
		index++;
	}
	tokens[tokens_len] = NULL;
	return (tokens);
}

char	****free_tokens(char *****tokens)
{
	// free();
	free(*tokens);
	*tokens = NULL;
	return (NULL);
}