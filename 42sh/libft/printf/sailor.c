/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sailor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 15:21:15 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/29 17:38:10 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static long		f2(t_out_s s, t_str in, t_beflags f, long y)
{
	f.field = y - (ft_wstrlen(s.win) + ft_strlen(s.output));
	if (f.field > 0)
	{
		if (!f.minus && !f.zero)
			if (!(ft_prechar(&s.output, ' ', f.field)))
				return (-1);
	}
	y = (ft_strlen(s.output) + ft_wstrlen(s.win) + ft_strlen(s.end_fl));
	(!s.win[0] && in.flags[0] == 'c') ? y += 1 : y;
	ft_putstr(in.display);
	ft_putstr(s.output);
	if (s.win[0] || in.flags[0] == 'c')
		if (!(ft_putwstr(s.win)))
			return (-1);
	ft_putstr(s.end_fl);
	ft_memdel((void **)&s.output);
	ft_memdel((void **)&s.end_fl);
	return (y);
}

static long		f1(t_out_s s, t_str in, t_beflags f, size_t x)
{
	long	y;
	int		size;

	s.end_fl = 0;
	if (!s.win[0] && in.flags[0] == 'c')
		f.field -= 1;
	y = f.field;
	size = f.field - (x + ft_strlen(s.output));
	if (size > 0)
	{
		if (f.minus)
		{
			if (!(ft_prechar(&s.end_fl, ' ', size)))
				return (-1);
		}
		else if (f.zero)
			if (!(ft_prechar(&s.output, '0', size)))
				return (-1);
	}
	return (f2(s, in, f, y));
}

long			sailor(wchar_t *insert, t_str in)
{
	t_beflags	f;
	t_out_s		s;
	size_t		x;

	s.output = 0;
	s.win = insert;
	x = ft_wstrlen(s.win);
	get_flags(&f, in.flags);
	if (f.precision != -1 && in.flags[0] != 'c')
	{
		if (in.flags[0] == 's')
		{
			if (f.precision < (int)x)
				w_precision(s.win, f.precision);
		}
		else if (f.precision > (int)x)
		{
			x -= f.precision;
			if (!(ft_prechar(&s.output, '0', x)))
				return (-1);
		}
	}
	if (!(print_local(s.win)))
		return (-1);
	return (f1(s, in, f, ft_wstrlen(s.win)));
}
