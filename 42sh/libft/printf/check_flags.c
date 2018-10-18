/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 19:49:01 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/29 17:33:29 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static long		end(wchar_t *w_out, char *insert, t_str in, long y)
{
	size_t	z;

	z = 0;
	if (w_out)
	{
		y = sailor(w_out, in);
		while (w_out[z])
			z += 1;
		ft_memset(w_out, 0, z);
		ft_memdel((void **)&w_out);
		return (y);
	}
	else if (insert)
	{
		y = captain_flag(insert, in);
		ft_memdel((void **)&insert);
		return (y);
	}
	return (-1);
}

static long		final(char *insert, va_list *arg_ft, t_str in, t_var every)
{
	int		y;

	y = -1;
	if (in.flags[0] == 'x')
	{
		if (!(insert = sea_x(arg_ft, in.flags, every)))
			return (-1);
	}
	else if (in.flags[0] == 'X')
	{
		if (!(insert = sea_x(arg_ft, in.flags, every)))
			return (-1);
		while (insert[++y])
			insert[y] = ft_toupper(insert[y]);
	}
	else if (in.flags[0] == 'd' || in.flags[0] == 'i' || in.flags[0] == 'D')
	{
		if (!(insert = sea_di(arg_ft, in.flags, every)))
			return (-1);
	}
	else
		return (-1);
	return (end(0, insert, in, 0));
}

static long		still(char *insert, va_list *arg_ft, t_str in, t_var every)
{
	if (in.flags[0] == 'p')
	{
		in.flags[ft_strlen(in.flags)] = '#';
		if (!(insert = ft_itoa_base_ulonglong(
		(unsigned long long)va_arg(*arg_ft, void *), "0123456789abcdef")))
			return (-1);
	}
	else if (in.flags[0] == 'o' || in.flags[0] == 'O')
	{
		if (!(insert = sea_o(arg_ft, in.flags, every)))
			return (-1);
	}
	else if (in.flags[0] == 'u' || in.flags[0] == 'U')
	{
		if (!(insert = sea_u(arg_ft, in.flags, every)))
			return (-1);
	}
	else
		return (final(insert, arg_ft, in, every));
	return (end(0, insert, in, 0));
}

static long		check(char *insert, va_list *arg_ft, t_str in, t_var every)
{
	if (in.flags[0] == 's')
	{
		if (!(insert = sea_s(arg_ft, every)))
			return (-1);
	}
	else if (in.flags[0] == 'c')
	{
		if (!(insert = sea_c(arg_ft, every)))
			return (-1);
	}
	else if (in.flags[0] == '%')
	{
		if (!(insert = ft_strdup("%")))
			return (-1);
	}
	else
		return (still(insert, arg_ft, in, every));
	return (end(0, insert, in, 0));
}

long			check_all(const char *format, size_t *x,
		va_list *arg_ft, t_str in)
{
	wchar_t	*w_out;
	char	*insert;
	t_var	every;
	long	y;

	every.d = 0;
	insert = 0;
	w_out = 0;
	if ((y = fill_flags(in.flags, format, x)) == -1)
		return (-1);
	if ((in.flags[0] == 's' && !y) || in.flags[0] == 'S')
	{
		(in.flags[0] == 'S') ? in.flags[0] = 's' : 1;
		if (!(w_out = sea_ws(arg_ft, every)))
			return (-1);
	}
	else if ((in.flags[0] == 'c' && !y) || in.flags[0] == 'C')
	{
		(in.flags[0] == 'C') ? in.flags[0] = 'c' : 1;
		if (!(w_out = sea_wc(arg_ft, every)))
			return (-1);
	}
	else
		return (check(insert, arg_ft, in, every));
	return (end(w_out, insert, in, 0));
}
