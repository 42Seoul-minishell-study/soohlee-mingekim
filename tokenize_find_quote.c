#include "minishell.h"

char	*find_next_single_quote(char *str)
{
	char	*temp;

	temp = str++;
	while (*str != '\0' && *str != '\'')
		str++;
	if (*str == '\0')
		return (temp);
	return (str);
}

char	*find_next_double_quote(char *str)
{
	char	*temp;

	temp = str++;
	while (*str != '\0' && *str != '\"')
		str++;
	if (*str == '\0')
		return (temp);
	return (str);
}