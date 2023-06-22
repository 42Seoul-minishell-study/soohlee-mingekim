/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:25:14 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/21 17:12:34 by soohlee          ###   ########.fr       */
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
	else if (word[0] == 'e')
	{
		ft_putstr_fd(word + 2, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		*flag_out = -1;
		return (0);
	}
	*flag_out = 0;
	return (0);
}

int	check_output(char *word, int *flag_out)
{
	if (ft_strncmp(word, "> ", 2) == 0)
	{
		*flag_out = O_WRONLY | O_TRUNC | O_CREAT;
		return (1);
	}
	else if (ft_strncmp(word, ">> ", 3) == 0)
	{
		*flag_out = O_WRONLY | O_CREAT | O_APPEND;
		return (1);
	}
	else if (word[0] == 'e')
	{
		ft_putstr_fd(word + 2, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		*flag_out = -1;
		return (0);
	}
	*flag_out = 0;
	return (0);
}
