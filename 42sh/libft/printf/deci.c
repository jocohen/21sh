/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 01:38:26 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:09:32 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*thor(va_list *arg_ft, char *insert, t_var every, t_flags fl)
{
	if (fl.h == 1)
	{
		every.h = va_arg(*arg_ft, unsigned int);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.h)))
			return (0);
		return (insert);
	}
	if (fl.h == 2)
	{
		every.c = va_arg(*arg_ft, unsigned int);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.c)))
			return (0);
		return (insert);
	}
	every.x = va_arg(*arg_ft, unsigned int);
	if (!(insert = ft_itoa_ulonglong((unsigned long long)every.x)))
		return (0);
	return (insert);
}

static char		*i_am(va_list *arg_ft, char *insert, t_var every, t_flags fl)
{
	if (fl.j == 1)
	{
		every.j = va_arg(*arg_ft, uintmax_t);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.j)))
			return (0);
		return (insert);
	}
	if (fl.l == 2)
	{
		every.ll = va_arg(*arg_ft, unsigned long long);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.ll)))
			return (0);
		return (insert);
	}
	if (fl.l == 1)
	{
		every.l = va_arg(*arg_ft, unsigned long);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.l)))
			return (0);
		return (insert);
	}
	return (thor(arg_ft, insert, every, fl));
}

static char		*luke(va_list *arg_ft, char *flags, t_var every, t_flags fl)
{
	char	*insert;

	insert = 0;
	if (flags[0] == 'U')
	{
		flags[0] = 'u';
		every.l = va_arg(*arg_ft, unsigned long);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.l)))
			return (0);
		return (insert);
	}
	if (fl.z == 1)
	{
		every.z = va_arg(*arg_ft, size_t);
		if (!(insert = ft_itoa_ulonglong((unsigned long long)every.z)))
			return (0);
		return (insert);
	}
	return (i_am(arg_ft, insert, every, fl));
}

char			*sea_u(va_list *arg_ft, char *flags, t_var every)
{
	t_flags	fl;
	size_t	y;

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
			fl.j += 1;
		else if (flags[y] == 'z')
			fl.z += 1;
		y += 1;
	}
	return (luke(arg_ft, flags, every, fl));
}
