/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 09:47:31 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:10:42 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*f4(va_list *arg_ft, char *flags, t_var every, t_flags fl)
{
	char	*insert;

	insert = 0;
	fl.z = every.d;
	if (fl.h == 2)
	{
		if ((every.hhd = va_arg(*arg_ft, int)) < 0)
			flags[fl.z] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.hhd)))
			return (0);
		return (insert);
	}
	if ((every.d = va_arg(*arg_ft, int)) < 0)
		flags[fl.z] = 'N';
	if (!(insert = ft_itoa_longlong((long long)every.d)))
		return (0);
	return (insert);
}

static char		*f3(va_list *arg_ft, char *flags, t_var every, t_flags fl)
{
	char	*insert;

	insert = 0;
	if (fl.l == 1)
	{
		fl.z = every.d;
		if ((every.ld = va_arg(*arg_ft, long)) < 0)
			flags[fl.z] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.ld)))
			return (0);
		return (insert);
	}
	else if (fl.h == 1)
	{
		fl.z = every.d;
		if ((every.hd = va_arg(*arg_ft, int)) < 0)
			flags[fl.z] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.hd)))
			return (0);
		return (insert);
	}
	return (f4(arg_ft, flags, every, fl));
}

static char		*f2(va_list *arg_ft, char *flags, t_var every, t_flags fl)
{
	char	*insert;

	insert = 0;
	if (fl.j == 1)
	{
		fl.l = every.d;
		if ((every.jd = va_arg(*arg_ft, intmax_t)) < 0)
			flags[fl.l] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.jd)))
			return (0);
		return (insert);
	}
	else if (fl.l == 2)
	{
		fl.z = every.d;
		if ((every.lld = va_arg(*arg_ft, long long)) < 0)
			flags[fl.z] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.lld)))
			return (0);
		return (insert);
	}
	return (f3(arg_ft, flags, every, fl));
}

static char		*f1(va_list *arg_ft, char *flags, t_var every, t_flags fl)
{
	char	*insert;

	insert = 0;
	if (flags[0] == 'D')
	{
		flags[0] = 'd';
		fl.l = every.d;
		if ((every.ld = va_arg(*arg_ft, long)) < 0)
			flags[fl.l] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.ld)))
			return (0);
		return (insert);
	}
	else if (fl.z == 1)
	{
		fl.l = every.d;
		if ((every.zd = va_arg(*arg_ft, ssize_t)) < 0)
			flags[fl.l] = 'N';
		if (!(insert = ft_itoa_longlong((long long)every.zd)))
			return (0);
		return (insert);
	}
	return (f2(arg_ft, flags, every, fl));
}

char			*sea_di(va_list *arg_ft, char *flags, t_var every)
{
	t_flags	fl;
	int		y;

	fl.h = 0;
	fl.l = 0;
	fl.j = 0;
	fl.z = 0;
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
	every.d = y;
	flags[y] = 'P';
	(flags[0] == 'i') ? flags[0] = 'd' : 1;
	return (f1(arg_ft, flags, every, fl));
}
