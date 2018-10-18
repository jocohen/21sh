/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:56:17 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:09:37 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		fill_flags(char *flags, const char *format, size_t *x)
{
	int		l;
	size_t	y;

	y = 1;
	l = 0;
	*x += 1;
	while (format[*x])
	{
		if (format[*x] == 's' || format[*x] == 'o' || format[*x] == 'u'
		|| format[*x] == 'x' || format[*x] == 'X' || format[*x] == 'c'
		|| format[*x] == '%' || format[*x] == 'S' || format[*x] == 'C'
		|| format[*x] == 'O' || format[*x] == 'U' || format[*x] == 'p'
		|| format[*x] == 'D' || format[*x] == 'O' || format[*x] == 'U'
		|| format[*x] == 'd' || format[*x] == 'i')
			break ;
		(format[*x] == 'l') ? l += 1 : 1;
		flags[y++] = format[(*x)++];
	}
	if (!format[*x])
		return (-1);
	flags[0] = format[*x];
	if (l)
		return (0);
	return (1);
}
