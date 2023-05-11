/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingekim <mingekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:28:15 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/11 16:00:10 by mingekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft.h"

//finish flags
# define EXIT 0
# define MALLOC_FAIL 1
# define SEARCH_DIR 2
# define ACCESS 3
# define COMMAND 4

//ect flags
# define STDOUT 0
# define STDIN 1
# define STDERR 2
# define PROMPT "minishell$ "

//args_check.c
int		args_check(int argc, char **argv, char **envp);

//signal
void	set_signal(void);
void	ctrl_c_handler(int signum);

//shell
void	loop_prompt(int argc, char **argv, char **envp);

//shell terminate
void	free_exit(int flag);
void	exit_print(int flag);

//interpreter.c
int		interpreter(char *str);

//pipe.c

#endif