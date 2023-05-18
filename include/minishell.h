/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:28:15 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/18 15:39:22 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
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

//parsing struct 'only sooha'
typedef struct s_string
{
	int	offset;
}		t_string;

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
int		interpreter(char *out_str, char **envp);

//parsing.c
int		translation(char *out_str, char *****out_data, char **envp);
int		shell_expansions(char *****out_data, char **envp);
int		convert_env(char *****out_data, char **envp);
int		single_quate(char **out_str, int *offset, char **envp);
int		double_quate(char **out_str, int *offset, char **envp);
char	*word_expanding(char *out_doulbe_str, char **envp);
char	*loop_expanding(char **out_str);
char	*small_word_expanding(char *out_small_str);
int		merge_word(char **out_str, char *out_middle_str, int start, int end);

//pipe.c

#endif