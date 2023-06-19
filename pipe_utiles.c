/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:31 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/19 17:05:31 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_and_exit(char *str, int exit_num)
{
	perror(str);
	exit(exit_num);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	set_fds_not_use(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

void	set_child_exit_status(void)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
}
