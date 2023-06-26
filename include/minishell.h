/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:28:15 by soohlee           #+#    #+#             */
/*   Updated: 2023/06/22 15:33:09 by soohlee          ###   ########.fr       */
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

typedef enum e_line_expand
{
	BEFORE_TOKENIZE = 0,
	AFTER_TOKENIZE = 1
}	e_line_expand;

int		g_exit_status;

//args_check.c
int		args_check(int argc, char **argv, char **envp);

//builtin.c
void	builtin(char **cmd, char ***env);
int		is_builtin(char **cmd);
int		error_exit_status(char *str, int num);
int		ft_twod_strlen(char **str);

//command_expand.c
void	cmd_expand(char ***token, char **env);

//command_expand_utils.c
void	free_cmd(char ***token);
char	*join_all_cmd(char ***token, char **env);

//command_line_expand.c
void	line_expand(char **cmd, char **env, int flag);

//command_line_expand_utils.c
void	skip_single_quote(char **cmd, int *offset);
void	skip_double_quote(char **cmd, int *offset);

//env_utils.c
size_t	get_env_name_len(char *str);
void	delete_env(char *env_name, char ***env_out, int delete_index);
void	free_env(char ***env);
char	*get_env(char *env_name, char **env);

//expand_utils.c
int		single_quote(char **tokens, int *offset);
int		double_quote(char **tokens, int *offset, char **env);
int		env_trans(char **tokens, int *offset, char **env);
char	*word_expand(char **tokens, char **env);

//free_exit.c
int		two_d_free_null(char ***str);
int		one_d_free_null(char **str);

//ft_cd.c
int		ft_cd(char **argv, char ***indepen_env);
int		change_home(char **argv, char **env);

//cd_utils.c
int		change_env(char *new_str, char *del_name, char ***indepen_env);
int		error_print(char *cmd, char *argv, char *messeage);

//ft_echo.c
int		ft_echo(char **argv);

//ft_env.c
char	**set_env(char **envp);
void	add_env(char *new_str, char ***env_out);
void	ft_env(char **env);
int		is_compare(char *compare, char **envp);

//ft_exit.c
int		ft_exit(char **argv, char ***env);

//ft_export.c
int		ft_export(char **argv, char ***env);

//ft_export_utils.c
int		make_sort_hash(int *sort_hash, char **env);
int		only_name_add(char *argv, char ***env);
int		print_export_oneline(char **env, int *i, int *j);

//ft_pwd.c
int		ft_pwd(void);

//ft_unset.c
int		ft_unset(char **argv, char ***env);

//heredoc.c
int		heredoc(char ****tokens, char **env, int *stdinout_copy);

//heredoc_utils.c
int		heredoc_unlink(char ****tokens);
int		make_heredocfile(char **filename);

//pipe.c
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
void	parsing_cmd_and_options(char **command, char **envp, int index);

//redirection_expand.c
int		redirection_expand(char ***tokens, char **env);

//shell_expand.c
int		shell_expand(char *****tokens, char **env);

//signal.c
void	set_signal(void);
int		stdin_dup2(int *stdinout_copy);
int		stdin_dup(int *stdinout_copy);
int		ctrl_d_continue(char *str);

//tokenize.c
char	****tokenize(char *str);

//tokenize_ops_and_words
int		is_redirection(char *str);
char	*skip_spaces_and_words(char *str, int redir_index, int *count_out);
void	get_ops_and_words_count(char *str, \
									int *ops_count_out, int *words_count_out);
void	split_ops_and_words(char *str, char ***ops_and_words_out);
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

#endif