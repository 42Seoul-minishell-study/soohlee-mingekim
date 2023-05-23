/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:09:28 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/11 16:01:04 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(char *word, int *flags_out)
{
	if (ft_strncmp(word, "<\0", 2) == 0)
	{
		*flags_out = O_RDONLY;
		return (1);
	}
	else if (ft_strncmp(word, "<<\0", 2) == 0)
	{
		*flags_out = O_RDONLY;
		return (1);
	}
	return (0);
}

int	check_output(char *word, int *flags_out)
{
	if (ft_strncmp(word, ">\0", 2) == 0)
	{
		*flags_out = O_WRONLY | O_CREAT;
		return (1);
	}
	else if (ft_strncmp(word, ">>\0", 2) == 0)
	{
		*flags_out = O_WRONLY | O_CREAT | O_APPEND;
		return (1);
	}
	return (0);
}

void	exec_command(void)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		return ;
	else if (cpid < 0)
	{
		perror("fork");
		exit(1);
	}
	// if (dup2(last_fd, STDIN_FILENO) < 0)
	// 	perror("dup2");
	// if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	// 	perror("dup2");
	//close(last_fd);
	//close(pipefd[0]);
	//close(pipefd[1]);
	//exeve();
	perror("execve");
}

int	pipes(void)
{
	
	return (0);
}

// int	operator_process(char ***cmds, char **envp)
// {
// 	int	*input_fds;
// 	int	*output_fds;
// 	int	pipe_fds[2][2];
// 
// 	if (set_fds_malloc(cmds, &input_fds, &output_fds) == 0)
// 	{
// 		return (0);
// 	}
// 	open_files_and_set_fds(cmds, &input_fds, &output_fds);
// 	//pipes
// 	//close fds
// 	//unlink files
// 	free(input_fds);
// 	free(output_fds);
// 	return (1);
// }
