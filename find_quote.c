#include "minishell.h"

char	*find_next_single_quote(char *str)
{
	while (*str != '\0' && *str != '\'')
	{
		if (ft_strncmp(str, "\'", 1) == 0)
		{
			while (ft_strncmp(str, "\'", 1) != 0)
			{
				if (*str == '\0')
					break ;
				str++;
			}
		}
		else
			str++;
	}
	return (str);
}

char	*find_next_double_quote(char *str)
{
	while (*str != '\0' && *str != '\"')
	{
		if (ft_strncmp(str, "\"", 1) == 0)
		{
			while (ft_strncmp(str, "\"", 1) != 0)
			{
				if (*str == '\0')
					break ;
				str++;
			}
		}
		else
			str++;
	}
	return (str);
}