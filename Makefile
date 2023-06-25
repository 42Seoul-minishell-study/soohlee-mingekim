NAME = minishell

SRCS = 	main.c \
		signal.c \
		args_check.c \
		free_exit.c \
		tokenize.c \
		tokenize_check.c \
		tokenize_ops_and_words.c \
		tokenize_ops.c \
		tokenize_words.c \
		tokenize_utils.c \
		tokenize_find_quote.c \
		translation.c \
		shell_expand.c \
		expand_utils.c \
		redirection_expand.c \
		command_expand.c \
		command_expand_utils.c \
		env_trim.c \
		env_utils.c \
		cd_utils.c \
		ft_export_utils.c \
		ft_echo.c \
		ft_cd.c \
		ft_pwd.c \
		ft_env.c \
		ft_export.c \
		ft_unset.c \
		ft_exit.c \
		pipe.c \
		pipe_check.c \
		pipe_cmd_parsing.c \
		pipe_get_fd.c \
		pipe_utiles.c \
		heredoc.c \
		heredoc_utils.c \
		builtin.c

CC = cc
LIBFT_DIR = ./libft
OBJS = $(SRCS:.c=.o)
CPPFLAGS = -I $(HOME)/.brew/opt/readline/include
LDFLAGS = -L $(HOME)/.brew/opt/readline/lib

#compile auto option
CFLAGS = -Wall -Wextra -Werror -g3

#header includes
INCLUDE = -I./include -I$(LIBFT_DIR)/include $(CPPFLAGS)

#library link
LIBFT_A = -L$(LIBFT_DIR) -lft

#log hide option
SILENT = -s

all : $(NAME)

$(NAME) : $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -lreadline -lhistory -o $(NAME);

$(LIBFT_A) :
	cd ./libft; make $(SILENT);

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean :
	cd ./libft; make $(SILENT) clean;
	rm -f $(OBJS);

fclean :
	cd ./libft; make $(SILENT) fclean;
	rm -f $(OBJS);
	rm -f $(NAME);

re :
	make $(SILENT) fclean;
	cd ./libft; make $(SILENT) re;
	make $(SILENT) all;

.SILENT : all $(NAME) $(OBJS) $(LIBFT_A) clean fclean re;