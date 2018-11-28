/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:01:56 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/26 11:41:13 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <wchar.h>
# include <unistd.h>
# include "ft_printf.h"
# include "get_next_line.h"

# define ANSI_RED					"\x1b[31m"
# define ANSI_GREEN					"\x1b[32m"
# define ANSI_YELLOW				"\x1b[33m"
# define ANSI_BLUE					"\x1b[34m"
# define ANSI_MAGENTA				"\x1b[35m"
# define ANSI_CYAN					"\x1b[36m"
# define ANSI_WHITE					"\x1b[97m"
# define ANSI_LIGHT_GRAY			"\x1b[47m"
# define ANSI_DARK_GRAY				"\x1b[100m"
# define ANSI_LIGHT_RED				"\x1b[101m"
# define ANSI_LIGHT_GREEN			"\x1b[102m"
# define ANSI_LIGHT_YELLOW			"\x1b[103m"
# define ANSI_LIGHT_BLUE			"\x1b[104m"
# define ANSI_LIGHT_MAGENTA			"\x1b[105m"
# define ANSI_LIGHT_CYAN			"\x1b[106m"

# define ANSI_DEF_BG				"\x1b[49m"
# define ANSI_RESET					"\x1b[0m"

# define ANSI_BOLD					"\e[1m"
# define ANSI_UNDERLINED			"\e[4m"
# define ANSI_BLINK					"\e[5m"
# define ANSI_BLACK					"\e[30m"
# define ANSI_MATRIX				"\e[5;32m"

size_t				ft_lenbyte(unsigned int c);
int					unicode_display(const wchar_t *input);
int					ft_putwstr(wchar_t const *s);
size_t				ft_wstrlen(const wchar_t *s);
int					ft_atoi_base(const char *s, int b);
void				ft_memdel2(char ***ap);
size_t				ft_strwhlen(const char *s, size_t start, size_t end);
void				*ft_memalloc(size_t size);
char				*ft_strcatc(char *s, int c);
char				*ft_strnew(size_t size);
char				*ft_strwhcpy(char *dst, char const *src, unsigned int start,
		unsigned int end);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strtrim(char const *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strstr(const char *haystack, const char *needle);
char				**ft_strsplit(char const *s, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char *));
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strdup(const char *s1);
void				ft_strdel(char **as);
char				*ft_strcpy(char *dst, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strclr(char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_itoa_base(int nb, const char *base);
char				*ft_strrev(char *str);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putstr(char const *s);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				*ft_memset(void *b, int c, size_t len);
int					ft_atoi(const char *s);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				ft_memdel0(char **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
typedef struct		s_l_dbl
{
	void			*content;
	size_t			content_size;
	struct s_l_dbl	*next;
	struct s_l_dbl	*prev;
}					t_l_dbl;

void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
unsigned int		ft_lstsize(t_list *lst);
t_list				*ft_lstfind(t_list *alst, void *data, int (*cmp)());
char				**ft_twod_dup(const char **t);
char				*ft_path(const char *path, char *file_name);
t_l_dbl				*ft_ldblnew(void const *content, size_t content_size);
int					ft_ldbldel(t_l_dbl **fp);

#endif
