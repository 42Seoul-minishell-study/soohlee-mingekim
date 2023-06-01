/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:16:38 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/01 21:41:26 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_tokens_print(char *****out_data);
// int		unlink_herefile(char ****tokens);

void	test_builtin(char ****tokens, char ***env)
{
	char	**argv;

	argv = tokens[0][1];
	if (!ft_strncmp(argv[0], "cd", 3))
		ft_cd(argv, env);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(argv[0], "echo", 5))
		ft_echo(argv);
	else if (!ft_strncmp(argv[0], "env", 4))
		ft_env(*env);
	else if (!ft_strncmp(argv[0], "export", 7))
		ft_export(argv, env);
	else if (!ft_strncmp(argv[0], "unset", 6))
		ft_unset(argv, env);
	// else if (!ft_strncmp(argv[0], "exit", 5))
	// 	ft_exit(argv, env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	****tokens;
	char	**env;

	set_signal();
	env = set_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		if (str != NULL && ft_strlen(str) != 0)
		{
			tokens = tokenize(str);
			if (tokens != NULL)
			{
				translation(&tokens, env);
//				test_builtin(tokens, &env);
				heredoc(tokens, env);
			//	execute(tokens, env);
				heredoc_unlink(tokens);
			//	free_tokens(&tokens);
			}  
			add_history(str);
			m_tokens_print(&tokens);
			heredoc_unlink(tokens);
		}
		if (!str)
			exit(0);
		free(str);
	}
	if (argc || argv || envp)
		;
	// operator_process(cmds, envp);
	// args_check(argc, argv, envp);
	// loop_prompt(argc, argv, envp);
	//free_env(&env);
	return (0);
}

void	m_tokens_print(char *****out_data)
{
	int	pipe;
	int	i;
	int	j;

	pipe = -1;
	printf("--------------------------after heredoc----------------------------\n");
	while ((*out_data)[++pipe])
	{
		i = -1;
		while ((*out_data)[pipe][++i])
		{
			j = -1;
			while ((*out_data)[pipe][i][++j])
				printf("%d %d %d: %s\n", pipe, i, j, (*out_data)[pipe][i][j]);
		}
	}
}

int	unlink_herefile(char ****tokens)
{
	int	process_idx;
	int	redir_idx;

	process_idx = -1;
	while (tokens[++process_idx])
	{
		redir_idx = -1;
		while (tokens[process_idx][0][++redir_idx])
		{
			if (!ft_strncmp(tokens[process_idx][0][redir_idx], "<< ", 3))
			{
				unlink(ft_strchr(tokens[process_idx][0][redir_idx], ' ') + 1);
			}
		}
	}
	return (0);
}
