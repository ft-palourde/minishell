/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:28:08 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/21 18:02:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
/* Returns if int c is digit. 1 if true. 0 if false. */
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char const *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_realloc(void *ptr, size_t size);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_printf(const char *str, ...);
int					ft_case_by_format(va_list ptr, char c);
int					ft_print_char(int c);
int					ft_print_str(char *str);
int					ft_print_ptr(unsigned long ptr);
int					ft_print_nbr(int nb);
int					ft_print_usnbr(unsigned long nb);
int					ft_print_hex_fmt(unsigned long nb, char c);
int					ft_putnbr_hexbase(unsigned long nb, char *hex_base);
void				ft_putchar(int c);
void				ft_putstr(char *str);
char				*extract_line(char *buf);
char				*get_buffer(int fd, char *buf);
char				*append_and_free(char *buf, char *buffer);
char				*get_next_line(int fd);
char				*update_buf(char *buf);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
int					is_in_base(char c, char *base);
int					is_base_valid(char *base);
void				*reverse_cascade_free(char **str, int i);

void				ft_swap(long *a, long *b);
char				*ft_strndup(const char *s, int n);
void				*reverse_cascade_free(char **str, int i);

#endif