
#include "minishell.h"

char	*get_env_name(char *cmd, char *last, char **env)
{
	char	*env_name;
	char	*temp;

	env_name = (char *)malloc(sizeof(char) * (last - cmd + 1));
	if (env_name == NULL)
		perror_and_exit("malloc", 1);
	ft_memset(env_name, 0, (last - cmd + 1));
	ft_memcpy(env_name, cmd, last - cmd);
	temp = get_env(env_name, env);
	free(env_name);
	return (temp);
}

char	*dup_with_len(char *str, char *last)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (last - str + 1));
	if (result == NULL)
		perror_and_exit("malloc", 1);
	ft_memset(result, 0, (last - str + 1));
	ft_memcpy(result, str, last - str);
	return (result);
}

char	*find_last(char *str, int flag)
{
	if (*str >= '0' && *str <= '9' && flag == 1)
		return (str + 1);
	while (*str != '\0' && *str != '$')
	{
		str++;
	}
	return (str);
}

// char	*find_last_in_quote(char *str, int flag)
// {
// 	if (*str >= '0' && *str <= '9' && flag == 1)
// 		return (str + 1);
// 	while (*str != '\0' && *str != '$' && *str != '\"')
// 	{
// 		str++;
// 	}
// 	return (str);
// }

