/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:31 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:32 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_and_return_zero(char *str)
{
	perror(str);
	return (0);
}

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
