#include "minishell.h"

char	*split_words(char *str, char **word_out)
{
	int		len;
	char	*temp;

	temp = find_next_word(str);
	len = temp - str;
	*word_out = malloc(sizeof(char) * (len + 1));
	if (*word_out == NULL)
	{
		perror("malloc");
		exit(1);
	}
	ft_memcpy(*word_out, str, len);
	(*word_out)[len] = '\0';
	return (temp);
}