/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:23:00 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:10:30 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		conditions(t_beflags *f, char *flags, size_t *x)
{
	if (flags[*x] == ' ')
		f->space = 1;
	else if (flags[*x] == '+')
		f->plus = 1;
	else if (flags[*x] == '.')
	{
		f->precision = 0;
		(flags[*x + 1] >= '0' && flags[*x + 1] <= '9') ? *x += 1 : 1;
		while (flags[*x] >= '0' && flags[*x] <= '9')
		{
			f->precision = f->precision * 10 + (flags[*x] - '0');
			*x += 1;
		}
		(flags[*x] != '.') ? *x -= 1 : 1;
	}
	else if (flags[*x] >= '0' && flags[*x] <= '9')
	{
		while (flags[*x] >= '0' && flags[*x] <= '9')
		{
			f->field = f->field * 10 + (flags[*x] - '0');
			*x += 1;
		}
		*x -= 1;
	}
}

void			get_flags(t_beflags *f, char *flags)
{
	size_t	x;

	x = 1;
	f->alt = 0;
	f->zero = 0;
	f->minus = 0;
	f->plus = 0;
	f->space = 0;
	f->neg = 0;
	f->precision = -1;
	f->field = 0;
	while (flags[x])
	{
		if (flags[x] == '#')
			f->alt = 1;
		else if (flags[x] == '0')
			f->zero = 1;
		else if (flags[x] == '-')
			f->minus = 1;
		else
			conditions(f, flags, &x);
		if (flags[x] == 'N')
			f->neg = 1;
		x += 1;
	}
}
