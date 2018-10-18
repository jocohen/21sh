/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 01:55:10 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:01 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*path(va_list *arg_ft, char *insert, t_var every, t_flags fl)
{
	if (fl.h == 1)
	{
		every.h = va_arg(*arg_ft, unsigned int);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.h,
		"01234567")))
			return (0);
		return (insert);
	}
	if (fl.h == 2)
	{
		every.c = va_arg(*arg_ft, unsigned int);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.c,
		"01234567")))
			return (0);
		return (insert);
	}
	every.x = va_arg(*arg_ft, unsigned int);
	if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.x,
	"01234567")))
		return (0);
	return (insert);
}

static char		*this(va_list *arg_ft, char *insert, t_var every, t_flags fl)
{
	if (fl.j == 1)
	{
		every.j = va_arg(*arg_ft, uintmax_t);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.j,
		"01234567")))
			return (0);
		return (insert);
	}
	if (fl.l == 2)
	{
		every.ll = va_arg(*arg_ft, unsigned long long);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.ll,
		"01234567")))
			return (0);
		return (insert);
	}
	if (fl.l == 1)
	{
		every.l = va_arg(*arg_ft, unsigned long);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.l,
		"01234567")))
			return (0);
		return (insert);
	}
	return (path(arg_ft, insert, every, fl));
}

static char		*follow(va_list *arg_ft, char *flags, t_var every, t_flags fl)
{
	char	*insert;

	insert = 0;
	if (flags[0] == 'O')
	{
		flags[0] = 'o';
		every.l = va_arg(*arg_ft, unsigned long);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.l,
		"01234567")))
			return (0);
		return (insert);
	}
	if (fl.z == 1)
	{
		every.z = va_arg(*arg_ft, size_t);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.z,
		"01234567")))
			return (0);
		return (insert);
	}
	return (this(arg_ft, insert, every, fl));
}

char			*sea_o(va_list *arg_ft, char *flags, t_var every)
{
	t_flags	fl;
	size_t	y;

	fl.h = 0;
	fl.l = 0;
	fl.z = 0;
	fl.j = 0;
	y = 0;
	while (flags[y])
	{
		if (flags[y] == 'l')
			fl.l += 1;
		else if (flags[y] == 'h')
			fl.h += 1;
		else if (flags[y] == 'j')
			fl.j = 1;
		else if (flags[y] == 'z')
			fl.z = 1;
		y += 1;
	}
	return (follow(arg_ft, flags, every, fl));
}
