/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 01:35:58 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:08:57 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static long		f4(t_out_s s, t_str in, t_beflags f, long y)
{
	if (in.flags[0] == 'd' && !f.neg)
	{
		if (f.plus)
		{
			if (!(ft_prestr(&s.output, "+", 1)))
				return (-1);
		}
		else if (f.space)
			if (!(ft_prestr(&s.output, " ", 1)))
				return (-1);
	}
	if (f.alt)
	{
		if ((in.flags[0] == 'x' || in.flags[0] == 'p') && f.neg != 3)
		{
			if (!(ft_prestr(&s.output, "0x", 2)))
				return (-1);
		}
		else if (in.flags[0] == 'X' && f.neg != 3)
			if (!(ft_prestr(&s.output, "0X", 2)))
				return (-1);
	}
	return (captain_2(s, in, f, y));
}

static long		f3(t_out_s s, t_str in, t_beflags f, long y)
{
	int		size;

	size = f.field - (ft_strlen(s.insert) + ft_strlen(s.output));
	if (size > 0)
	{
		if (f.minus)
		{
			if (!(ft_prechar(&s.end_fl, ' ', size)))
				return (-1);
		}
		else if (f.zero && (f.precision == -1 || in.flags[0] == 's' ||
		in.flags[0] == 'c' || in.flags[0] == '%'))
			if (!(ft_prechar(&s.output, '0', size)))
				return (-1);
	}
	if (f.neg == 1)
		if (!(ft_prestr(&s.output, "-", 1)))
			return (-1);
	return (f4(s, in, f, y));
}

static long		f2(t_out_s s, t_str in, t_beflags f, long y)
{
	s.end_fl = 0;
	if (f.alt)
	{
		if (in.flags[0] == 'o' && f.precision <= 0 &&
		ft_atoi(s.insert) && !f.zero)
			f.field -= 1;
		else if ((in.flags[0] == 'x' || in.flags[0] == 'X' ||
		in.flags[0] == 'p') && f.neg != 3)
			f.field -= 2;
	}
	if ((in.flags[0] == 'd' && !f.neg && (f.plus || f.space)) || f.neg == 1)
		f.field -= 1;
	return (f3(s, in, f, y));
}

static long		f1(t_out_s s, t_str in, t_beflags f, size_t x)
{
	long	y;

	s.output = 0;
	if (f.precision != -1 && in.flags[0] != 'c' && in.flags[0] != '%')
	{
		if (in.flags[0] == 's')
		{
			if (f.precision < (int)x)
				ft_memset((s.insert + f.precision), 0,
				ft_strlen(s.insert + f.precision));
		}
		else if (f.precision > (int)x)
		{
			y = 0;
			(f.neg == 1) ? y += 1 : 1;
			y += f.precision - x;
			if (!(s.output = ft_memalloc(y + 1)))
				return (-1);
			ft_memset(s.output, '0', y);
			(f.neg == 1) ? s.output[0] = '-' : 1;
			(f.neg == 1) ? f.neg = 2 : 1;
		}
	}
	return (f2(s, in, f, f.field));
}

long			captain_flag(char *insert, t_str in)
{
	t_beflags	f;
	t_out_s		s;
	size_t		x;

	s.insert = insert;
	x = ft_strlen(s.insert);
	get_flags(&f, in.flags);
	if ((in.flags[0] == 'x' || in.flags[0] == 'X') && (s.insert[0] == '0'
	&& !s.insert[1]))
		f.neg = 3;
	if (s.insert[0] == '0' && !s.insert[1] && f.precision > -1)
	{
		if (in.flags[0] == 'x' || in.flags[0] == 'd' || in.flags[0] == 'X'
		|| in.flags[0] == 'u' || in.flags[0] == 'p')
			ft_memset(s.insert, 0, x);
		else if (in.flags[0] == 'o' && !f.alt)
			ft_memset(s.insert, 0, x);
	}
	if (f.alt && in.flags[0] == 'o' && f.precision <= (int)x &&
	ft_atoi(s.insert) && (!f.zero || f.precision > -1 || f.field <= (int)x))
		f.precision = x + 1;
	if (!s.insert[0] && in.flags[0] == 'c')
		f.field -= 1;
	return (f1(s, in, f, ft_strlen(s.insert)));
}
