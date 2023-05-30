/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:28:15 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/30 17:00:15 by soohlee          ###   ########.fr       */
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
typedef struct s_retokendata
{
	int		all_space_check;
	int		front_space_exist;
	int		start;
	int		*offset;
	int		*cmd_num;
	int		insert_str_len;
	char	*front_str;
	char	*end_str;
}		t_retokendata;

//free
void 	two_d_free(char **str);

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

//pipe.c
int		operator_process(char ***cmds, char **envp);

//tokenize.c
char	****tokenize(char *str);

//tokenize_ops_and_words
char	**set_ops_and_words(char *str, char ***ops_and_words_out);

//tokenize_find_quote.c
char	*find_next_single_quote(char *str);
char	*find_next_double_quote(char *str);

char	*find_next_word(char *str);

//tokenize_ops.c
char	*split_ops(char *str, char **op_out);

//tokenize_words.c
char	*split_words(char *str, char **word_out);

//tokenize_utils.c
char	*find_next_pipe(char *str);
char	*find_next_word(char *str);
char	*pass_space(char *str);
int		is_redirection(char *str);
char	****free_tokens(char *****tokens);

int		tokens_check(char *****tokens);

//translation.c
int		translation(char *****out_data, char **envp);
//shell_expansions.c
int		shell_expand(char *****out_data, char **envp);
int		redirection_expand(char ***out_redir, char **envp);
int		cmd_expand(char ***out_cmd, char **envp);
//redirection_expand
int		redir_line_expand(char **out_one_line, char **envp);	//한줄만 확장시 사용가능. heredoc의 피연산자는 확장안하는 기능가짐.
int		redir_env_trans(char **out_str, int *offset, char **envp);
//cmd_expand
int		cmd_line_expand(char ***out_cmd, int *cmd_num, char **envp);	//한줄만 확장시 사용가능.
int		cmd_env_trans(char ***out_cmd, int *cmd_num, int *offset, char **envp);
int		re_tokenize(char ***out_cmd, t_retokendata db, char *out_insert_str);
int		insert_two_d_array(char ***out_cmd, t_retokendata db, char **insert_twod_array, int twod_len);
//expand_utils
int		single_quate(char **out_str, int *offset, char **envp);
int		double_quate(char **out_str, int *offset, char **envp);
char	*word_expand(char **out_str, char **envp);
int		env_trans(char **out_str, int *offset, char **envp);

//env_utils.c
char	**set_env(char **envp);
void	add_env(char *new_str, char ***env_out);
char	*get_env(char *env_name, char **env);
void	delete_env(char *env_name,char ***env_out);
void	free_env(char ***env);
void	print_env(char **env);
char	*get_env(char *env_name, char **env);

//ft_echo.c
int		ft_echo(char **argv);
int		option_remove(char ***argv);

//ft_cd.c
int		ft_cd(char **argv, char ***indepen_env);

//ft_pwd.c
int		ft_pwd(void);

//ft_env.c
void	ft_env(char **env);

#endif