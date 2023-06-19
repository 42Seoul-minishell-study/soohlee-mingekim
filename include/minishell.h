/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:28:15 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/19 23:38:26 by soohlee          ###   ########.fr       */
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

typedef enum e_ctrl
{
	CTRL_C = -1,
	CTRL_C_COUNT = 2
}	t_ctrl;

//parsing struct 'only sooha'
typedef struct s_retoken
{
	int		last_flag;
	int		all_space_check;
	int		front_space_exist;
	int		tail_space_exist;
	int		start;
	int		*offset;
	int		*cmd_num;
	int		insert_str_len;
	char	*front;
	char	*end;
	char	**insert_twod;
	int		twod_len;
	int		cmdtotal;
}		t_retoken;

//global variable
int		g_exit_status;

//free
int		two_d_free_null(char ***str);
int		one_d_free_null(char **str);

//args_check.c
int		args_check(int argc, char **argv, char **envp);

//signal
void	set_signal(void);
void	ctrl_c_handler(int signum);
int		stdin_dup2(int *stdinout_copy);
int		stdin_dup(int *stdinout_copy);
int		ctrl_d_continue(char *str);
// int		ctrl_d_exit(char *str, int *stdinout_copy);

//shell terminate
void	free_exit(int flag);
void	exit_print(int flag);

//tokenize.c
char	****tokenize(char *str);

//tokenize_ops_and_words
int		is_redirection(char *str);
char	**set_ops_and_words(char *str, char ***ops_and_words_out);

//tokenize_find_quote.c
char	*find_next_single_quote(char *str);
char	*find_next_double_quote(char *str);

//tokenize_ops.c
char	*split_ops(char *str, char **op_out);

//tokenize_words.c
char	*split_words(char *str, char **word_out);

//tokenize_utils.c
int		is_space(char ch);
char	*find_next_pipe(char *str);
char	*find_next_word(char *str);
char	*pass_space(char *str);
char	****free_tokens(char *****tokens);

//tokenize_check.c
int		tokens_check(char *****tokens);

//translation.c
int		translation(char *****tokens, char **envp);

//shell_expansions.c
int		shell_expand(char *****tokens, char **env);
int		redirection_expand(char ***tokens, char **env);
int		cmd_expand(char ***tokens, char **env);

//redirection_expand
int		redir_line_expand(char **tokens, char **envp);
int		redir_env_check(char **tokens, int *offset, char **envp);
int		redir_env_trans(char **tokens, int *start, int *offset, char **env);

//cmd_expand
int		cmd_line_expand(char ***tokens, int *cmd_num, char **env);
int		cmd_env_check(char ***tokens, int *cmd_num, int *offset, char **env);
int		cmd_env_trans(char ***tokens, t_retoken *db, char **env);
int		re_tokenize(char ***tokens, t_retoken db, char *out_insert_str);
int		insert_two_d_array(char ***tokens, t_retoken db);
int		mid_insert(t_retoken *db, char ***new_cmd, int *idx, int *insert_idx);
int		mi_isalnum(int c);

//expand_utils
int		single_quate(char **tokens, int *offset);
int		double_quate(char **tokens, int *offset, char **env);
char	*word_expand(char **tokens, char **env);
int		env_trans(char **tokens, int *offset, char **env);

//env_utils.c
char	*get_env(char *env_name, char **env);
void	delete_env(char *env_name, char ***env_out);
void	free_env(char ***env);
size_t	get_env_name_len(char *str);

//ft_echo.c
int		ft_echo(char **argv);
int		option_remove(char ***argv);
int		ehco_print(char **argv);

//ft_exit.c
int		ft_exit(char **argv, char ***env);

//ft_cd.c
int		ft_cd(char **argv, char ***indepen_env);

//ft_pwd.c
int		ft_pwd(void);

//ft_env.c
char	**set_env(char **envp);
void	add_env(char *new_str, char ***env_out);
void	print_env(char **env);
void	ft_env(char **env);

//ft_export.c
int		ft_export(char **argv, char ***env);
int		only_name_add(char *argv, char ***env);

//ft_unset.c
int		ft_unset(char **argv, char ***env);

//pipe.c
int		is_builtin(char **cmd);
int		execute(char *****tokens, char ***envp, int *ctrl_cnt);

//pipe_check.c
int		check_input(char *word, int *flag_out);
int		check_output(char *word, int *flag_out);

//pipe_utile.c
int		perror_and_exit(char *str, int exit_num);
void	close_fd(int fd);
void	set_fds_not_use(int *fd);
void	set_child_exit_status(void);

//pipe_get_fd.c
int		get_infile_fd(char ***token, int *last_pipe_fd_out);
int		get_outfile_fd(char ***token, int *pipe_fd_out);

//pipe_cmd_parsing.c
void	parsing_cmd_and_options(char **command_out, char **envp);

//heredoc.c
int		heredoc(char ****tokens, char **env, int *stdinout_copy);
int		heredoc_unlink(char ****tokens);

//builtin.c
void	builtin(char **cmd, char ***env);
int		is_builtin(char **cmd);

#endif