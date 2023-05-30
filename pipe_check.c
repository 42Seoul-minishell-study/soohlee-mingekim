/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:14 by mingekim          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:16 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(char *word, int *flag_out)
{
	if (ft_strncmp(word, "< ", 2) == 0)
	{
		*flag_out = O_RDONLY;
		return (1);
	}
	else if (ft_strncmp(word, "<< ", 3) == 0)
	{
		*flag_out = O_RDONLY;
		return (1);
	}
	*flag_out = 0;
	return (0);
}

int	check_output(char *word, int *flag_out)
{
	if (ft_strncmp(word, "> ", 2) == 0)
	{
		*flag_out = O_WRONLY | O_CREAT;
		return (1);
	}
	else if (ft_strncmp(word, ">> ", 3) == 0)
	{
		*flag_out = O_WRONLY | O_CREAT | O_APPEND;
		return (1);
	}
	*flag_out = 0;
	return (0);
}
