/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:30:11 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/16 14:01:49 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//libft
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//ft_printf
int		ft_printf(const char *arg, ...);
int		ft_prf_putchar_fd(char c, int fd, int *prfcnt);
int		ft_prf_putstr_fd(char *s, int fd, int *prfcnt);
size_t	ft_prf_strlen(const char *s);
int		ft_prf_putnbr_fd(int n, int fd, int *prfcnt);
int		ft_prf_put_addrhex(void *ap, int *prfcnt, int fd);
int		ft_prf_put_hex(unsigned int ap, int *prfcnt, char format, int fd);
int		ft_prf_unsigned_putnbr_fd(unsigned int n, int fd, int *prfcnt);

//get_next_line
typedef struct s_fileinfo
{
	int					fd;
	char				*backup;
	struct s_fileinfo	*next;
}						t_fileinfo;
char	*get_next_line(int fd);

char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_substr(char *s, unsigned int start, size_t len);
size_t	ft_gnl_strlen(const char *s);
char	*ft_gnl_strdup(const char *s1);
size_t	ft_gnl_strchr(const char *s, int c);

//push_swap
int		ft_atoi_no_overflow(const char *str);

//piscine
void	ft_sort_int_tab(int *tab, int size);

//my_function
char	*ft_strinsert(char *str, char *insert_str, int del_start, int del_len);

#endif
