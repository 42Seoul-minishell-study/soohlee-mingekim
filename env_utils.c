#include "minishell.h"

char	**set_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	add_env(char *new_str, char ***env_out)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env_out)[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (++i + 1));
	i = 0;
	while ((*env_out)[i] != NULL)
	{
		new_env[i] = (*env_out)[i];
		i++;
	}
	new_env[i++] = new_str;
	new_env[i] = NULL;
	free(*env_out);
	*env_out = new_env;
}

static int	get_env_name_len(char *str)
{
	char	*temp;

	temp = ++str;
	while (*temp != '=')
		temp++;
	return (temp - str);
}

void	delete_env(char *env_name,char ***env_out)
{
	int		i;
	int		j;
	int		delete_index;
	char	**new_env;

	i = -1;
	while ((*env_out)[++i] != NULL)
	{
		if (ft_strncmp((*env_out)[i], env_name, get_env_name_len((*env_out)[i])) == 0)
			delete_index = i;
	}
	new_env = malloc(sizeof(char *) * i);
	i = -1;
	j = 0;
	while ((*env_out)[++i] != NULL)
	{
		if (i == delete_index)
		{
			free((*env_out)[i]);
			continue ;
		}
		new_env[j++] = (*env_out)[i];
	}
	new_env[j] = NULL;
	free(*env_out);
	*env_out = new_env;
}

void	free_env(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		free((*env)[i]);
		i++;
	}
	free((*env));
	*env = NULL;
}

char	*get_env(char *env_name, char **env)
{
	int		i;
	int		find_index;
	char	*temp;
	char	*str_env;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], env_name, get_env_name_len(env[i])) == 0)
			find_index = i;
	}
	temp = ft_strchr(env[i], '=');
	++temp;
	str_env = ft_strdup(temp);
	return (str_env);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	printf("-----------------env-----------------\n");
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("-----------------env-----------------\n");
}