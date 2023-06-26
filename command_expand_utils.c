
#include "minishell.h"

void	free_cmd(char ***token)
{
	int	i;

	i = 0;
	while (token[1][i] != NULL)
	{
		free(token[1][i]);
		i++;
	}
	free(token[1]);
}

char	*join_all_cmd(char ***token, char **env)
{
	int		index;
	char	*cmds_temp;
	char	*expanded;
	char	*result;

	index = 0;
	expanded = line_expand_1(token[1][index], env);
	result = mi_strjoin("", expanded);
	free(expanded);
	while (token[1][++index] != NULL)
	{
		expanded = line_expand_1(token[1][index], env);
		cmds_temp = mi_strjoin(result, expanded);
		free(result);
		free(expanded);
		result = cmds_temp;
	}
	return (result);
}

int	is_expand_needed(char **cmds)
{
	char	*str;
	char	*temp;

	while (*cmds != NULL)
	{
		str = *cmds;
		while (*str != '\0' && *str != '$')
		{
			str = pass_space(str);
			while (*str != '\0' && is_space(*str) == 0 && *str != '$')
			{
				if (*str == '\'')
					str = find_next_single_quote(str);
				else if (*str == '\"')
				{
					temp = str;
					str = find_next_double_quote(str);
					if (*str == '\"')
					{
						while (*temp != '\0'&& *temp != '$')
							temp++;
						if (*temp == '$')
							return (1);
					}
				}
				str++;
			}
		}
		cmds++;
	}
	if (*str == '$')
		return (1);
	return (0);
}
