/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 15:15:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/29 17:37:17 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static long		ft2(va_list *arg_ft, const char *format, size_t *x, t_str *in)
{
	int		error;
	long	y;

	y = 0;
	if ((error = count_flags(format, (*x), &(in->flags))) == -1)
	{
		ft_memdel((void **)&(in->display));
		return (-1);
	}
	else if (error == -2)
	{
		if ((y = check_all(format, x, arg_ft, *in)) == -1)
		{
			ft_memdel((void **)&(in->flags));
			ft_memdel((void **)&(in->display));
			return (-1);
		}
		*x += 1;
	}
	else
	{
		*x = error;
		ft_putstr(in->display);
	}
	return (y);
}

static long		ft1(va_list *arg_ft, const char *format, t_str in)
{
	int			end;
	long		y;
	size_t		x;
	long		w;

	y = 0;
	end = 2;
	x = 0;
	while (end != 1)
	{
		w = x;
		if (!(end = until_percent(format, &x, &(in.display))))
			return (-1);
		y = y + (x - w);
		if (end == 2)
		{
			if ((w = ft2(arg_ft, format, &x, &in)) == -1)
				return (-1);
			y += w;
		}
		else
			ft_putstr(in.display);
		ft_mult_del(&(in.display), &(in.flags));
	}
	return (y);
}

int				ft_printf(const char *format, ...)
{
	t_str		in;
	va_list		arg_ft;
	long		y;

	y = 0;
	in.flags = 0;
	in.display = 0;
	va_start(arg_ft, format);
	y = ft1(&arg_ft, format, in);
	if (y == -1)
		return (-1);
	va_end(arg_ft);
	return (y);
}
