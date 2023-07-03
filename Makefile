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
		command_line_expand.c \
		command_line_expand_utils.c \
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
LIBFT_OBJS = ./libft/srcs/*.o
OBJS = $(SRCS:.c=.o)
CPPFLAGS = -I $(HOME)/.brew/opt/readline/include
LDFLAGS = -L $(HOME)/.brew/opt/readline/lib

#compile auto option
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

#header includes
INCLUDE = -I./include -I$(LIBFT_DIR)/include $(CPPFLAGS)

#library link
LIBFT_A = -L$(LIBFT_DIR) -lft

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT_A) -lreadline -lhistory -o $(NAME)

$(LIBFT_OBJS) :
	cd ./libft; make

clean :
	cd ./libft; make clean;
	rm -f $(OBJS);

fclean :
	cd ./libft; make fclean;
	rm -f $(OBJS);
	rm -f $(NAME);

re :
	make fclean;
	cd ./libft; make re;
	make all;
