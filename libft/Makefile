SRCS =	ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c \
		ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c \
		ft_substr.c ft_strdup.c ft_calloc.c ft_atoi.c ft_strnstr.c \
		ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_tolower.c \
		ft_toupper.c ft_strlcpy.c ft_isprint.c ft_strlcpy.c ft_bzero.c \
		ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_strlcat.c ft_strlen.c ft_strncmp.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c \
		get_next_line_utils.c ft_printf.c ft_prf_put_addrhex.c \
		ft_prf_put_hex.c ft_prf_unsigned_putnbr_fd.c ft_prf_putchar_fd.c \
		ft_prf_putnbr_fd.c ft_prf_putstr_fd.c ft_prf_strlen.c ft_atoi_no_overflow.c \
		ft_sort_int_tab.c

SRCDIR = $(addprefix ./srcs/, $(SRCS))
OBJS = $(SRCDIR:.c=.o)
INCLUDE = -I./include
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
AR = ar
ARFLAGS = rc

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all