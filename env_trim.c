
#include "minishell.h"

char	*find_next_quote_trim(char *str, char ch)
{
	str++;
	while (*str != '\0' && *str != ch)
		str++;
	return (str);
}

static int	get_env_var_len(char *str)
{
	int		count;
	char	*temp;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '\'')
		{
			temp = find_next_quote_trim(str, '\'');
			if (*temp == '\'')
			{
				count += temp - str - 1;
				str = temp + 1;
			}
			else
			{
				str++;
				count++;
			}
		}
		else if (*str == '\"')
		{
			temp = find_next_quote_trim(str, '\"');
			if (*temp == '\"')
			{
				count += temp - str - 1;
				str = temp + 1;
			}
			else
			{
				str++;
				count++;
			}
		}
		else
		{
			str++;
			count++;
		}
	}
	return (count);
}

char	*trim_quotes(char *str)
{
	int		len;
	char	*temp;
	char	*temp_str;
	char	*result;

	len = get_env_var_len(str);
	printf("env_var len : %d\n", len);
	result = (char *)malloc(sizeof(char) * (len + 1));
	temp = result;
	while (*str != '\0')
	{
		if (*str == '\'')
		{
			temp_str = find_next_quote_trim(str, '\'');
			if (*temp_str == '\'')
			{
				ft_memcpy(temp, str + 1, temp_str - str - 1);
				temp += temp_str - str - 1;
				str = temp_str + 1;
			}
			else
				*temp++ = *str++;
		}
		else if (*str == '\"')
		{
			temp_str = find_next_quote_trim(str, '\"');
			if (*temp_str == '\"')
			{
				ft_memcpy(temp, str + 1, temp_str - str - 1);
				temp += temp_str - str - 1;
				str = temp_str + 1;
			}
			else
				*temp++ = *str++;
		}
		else
			*temp++ = *str++;
	}
	result[len] = '\0';
	printf("trim %s\n", result);
	return (result);
}