/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 01:38:26 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:10:36 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*a_nice_person(va_list *arg_ft, char *insert, t_var every)
{
	every.x = va_arg(*arg_ft, unsigned int);
	if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.x,
	"0123456789abcdef")))
		return (0);
	return (insert);
}

static char		*is(va_list *arg_ft, char *insert, t_var every, t_flags fl)
{
	if (fl.l == 1)
	{
		every.l = va_arg(*arg_ft, unsigned long);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.l,
		"0123456789abcdef")))
			return (0);
		return (insert);
	}
	if (fl.h == 1)
	{
		every.h = va_arg(*arg_ft, unsigned int);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.h,
		"0123456789abcdef")))
			return (0);
		return (insert);
	}
	if (fl.h == 2)
	{
		every.c = va_arg(*arg_ft, unsigned int);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.c,
		"0123456789abcdef")))
			return (0);
		return (insert);
	}
	return (a_nice_person(arg_ft, insert, every));
}

static char		*ur_mum(va_list *arg_ft, char *insert, t_var every, t_flags fl)
{
	if (fl.z == 1)
	{
		every.z = va_arg(*arg_ft, size_t);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.z,
		"0123456789abcdef")))
			return (0);
		return (insert);
	}
	if (fl.j == 1)
	{
		every.j = va_arg(*arg_ft, uintmax_t);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.j,
		"0123456789abcdef")))
			return (0);
		return (insert);
	}
	if (fl.l == 2)
	{
		every.ll = va_arg(*arg_ft, unsigned long long);
		if (!(insert = ft_itoa_base_ulonglong((unsigned long long)every.ll,
		"0123456789abcdef")))
			return (0);
		return (insert);
	}
	return (is(arg_ft, insert, every, fl));
}

char			*sea_x(va_list *arg_ft, char *flags, t_var every)
{
	char	*insert;
	t_flags	fl;
	size_t	y;

	fl.h = 0;
	fl.l = 0;
	fl.j = 0;
	fl.z = 0;
	insert = 0;
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
	return (ur_mum(arg_ft, insert, every, fl));
}
