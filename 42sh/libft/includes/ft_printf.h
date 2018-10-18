/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 15:54:40 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/18 14:03:03 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <wchar.h>
# include <stdarg.h>
# include <limits.h>

typedef union			u_var
{
	int					d;
	signed char			hhd;
	short				hd;
	long				ld;
	long long			lld;
	intmax_t			jd;
	ssize_t				zd;
	unsigned short		h;
	unsigned long		l;
	unsigned long long	ll;
	uintmax_t			j;
	size_t				z;
	int					i;
	unsigned char		c;
	char				*s;
	void				*p;
	wchar_t				*ls;
	wint_t				lc;
	unsigned int		o;
	unsigned int		u;
	unsigned int		x;
}						t_var;

typedef struct			s_flags
{
	int					h;
	int					l;
	int					j;
	int					z;
}						t_flags;

typedef struct			s_beflags
{
	int					alt;
	int					zero;
	int					minus;
	int					plus;
	int					space;
	int					neg;
	int					field;
	int					precision;
}						t_beflags;

typedef struct			s_str
{
	char				*display;
	char				*flags;
}						t_str;

typedef struct			s_out_s
{
	char				*output;
	char				*insert;
	wchar_t				*win;
	char				*end_fl;
}						t_out_s;

long					captain_2(t_out_s s, t_str in, t_beflags f, long y);
void					ft_mult_del(char **a, char **b);
int						ft_prestr(char **output, const char *str, size_t x);
int						ft_prechar(char **output, int c, size_t s);
void					get_flags(t_beflags *f, char *flags);
int						fill_flags(char *flags, const char *format, size_t *x);
int						ft_printf(const char *format, ...);
char					*sea_c(va_list *arg_ft, t_var every);
char					*sea_s(va_list *arg_ft, t_var every);
char					*sea_di(va_list *arg_ft, char *flags, t_var every);
char					*sea_u(va_list *arg_ft, char *flags, t_var every);
char					*sea_o(va_list *arg_ft, char *flags, t_var every);
char					*sea_x(va_list *arg_ft, char *flags, t_var every);
wchar_t					*sea_wc(va_list *arg_ft, t_var every);
wchar_t					*sea_ws(va_list *arg_ft, t_var every);
void					w_precision(wchar_t *insert, int precision);
long					check_all(const char *input, size_t *x,
						va_list *arg_ft, t_str in);
long					captain_flag(char *insert, t_str in);
long					sailor(wchar_t *insert, t_str in);
int						print_local(const wchar_t *input);
int						count_flags(const char *input, size_t x,
						char **flags);
int						until_percent(const char *input, size_t *x,
						char **display);

char					*ft_itoa_ulonglong(unsigned long long n);
char					*ft_itoa_base_ulonglong(unsigned long long nb,
						const char *base);
char					*ft_itoa_longlong(long long n);

#endif
