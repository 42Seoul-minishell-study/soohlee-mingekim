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

int	set_fds_malloc(char ***cmds, int **input_fds_out, int **output_fds_out)
{
	int	cmds_len;

	cmds_len = 0;
	while (cmds[cmds_len] != NULL)
		cmds_len++;
	*input_fds_out = (int *)malloc(sizeof(int) * cmds_len);
	if (*input_fds_out == NULL)
	{
		perror("malloc");
		return (0);
	}
	*output_fds_out =  (int *)malloc(sizeof(int) * cmds_len);
	if (*output_fds_out == NULL)
	{
		free(*input_fds_out);
		perror("malloc");
		return (0);
	}
	return (1);
}

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

int	get_input_fd(char **cmd)
{
	int	cmd_index;
	int	fd;
	int	last_redirection_index;
	int	flags;

	cmd_index = 0;
	fd = -1;
	last_redirection_index = -1;
	while (cmd[cmd_index] != NULL)
	{
		if (check_input(cmd[cmd_index], &flags) == 1)
		{
			if (last_redirection_index != -1)
				close(fd);
			fd = open(cmd[cmd_index + 1], flags);
			if (fd < 0)
				perror("open");
			last_redirection_index = cmd_index;
		}
		cmd_index++;
	}
	if (last_redirection_index != -1)
		return (fd);
	return (-1);
}

int		get_output_fd(char **cmd)
{
	int	cmd_index;
	int	fd;
	int	last_redirection_index;
	int	flags;

	cmd_index = 0;
	fd = -1;
	last_redirection_index = -1;
	while (cmd[cmd_index] != NULL)
	{
		if (check_output(cmd[cmd_index], &flags) == 1)
		{
			if (last_redirection_index != -1)
				close(fd);
			fd = open(cmd[cmd_index + 1], flags, 0644);
			if (fd < 0)
				perror("open");
			last_redirection_index = cmd_index;
		}
		cmd_index++;
	}
	if (last_redirection_index != -1)
		return (fd);
	return (-1);
}

void	open_files_and_set_fds(char ***cmds, int **input_fds_out, \
								int **output_fds_out)
{
	int		cmds_len;
	int		cmds_index;

	cmds_len = 0;
	while (cmds[cmds_len] != NULL)
		cmds_len++;
	cmds_index = 0;
	while (cmds[cmds_index] != NULL)
	{
		(*input_fds_out)[cmds_index] = get_input_fd(cmds[cmds_index]);
		(*output_fds_out)[cmds_index] = get_output_fd(cmds[cmds_index]);
		cmds_index++;
	}
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
