/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_expand_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:34:32 by mingekim          #+#    #+#             */
/*   Updated: 2023/06/26 15:34:35 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_single_quote(char **cmd, int *offset)
{
	char	*temp;

	temp = (*cmd) + *offset;
	temp = find_next_single_quote(temp);
	*offset += temp - (*cmd);
}

void	skip_double_quote(char **cmd, int *offset)
{
	char	*temp;

	temp = (*cmd) + *offset;
	temp = find_next_double_quote(temp);
	*offset += temp - (*cmd) + 1;
}
