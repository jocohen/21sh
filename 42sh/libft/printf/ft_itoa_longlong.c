/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_longlong.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 06:58:35 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:09:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		digit(long long n, size_t x)
{
	size_t	d;
	int		num;

	d = 1;
	while ((n / 10) && d < x)
	{
		n = n / 10;
		d += 1;
	}
	num = n % 10;
	return (num + '0');
}

static size_t	n_digit(long long n)
{
	size_t	d;

	d = 1;
	while ((n / 10))
	{
		n = n / 10;
		d += 1;
	}
	return (d);
}

char			*ft_itoa_longlong(long long n)
{
	size_t	d;
	int		max;
	char	*output;

	output = 0;
	max = 0;
	d = n_digit(n);
	if (n < 0 && n == LONG_MIN)
	{
		n += 1;
		max = 1;
	}
	(n < 0) ? n *= -1 : 1;
	if (!(output = ft_strnew(d)))
		return (0);
	while (d)
	{
		output = ft_strcatc(output, digit(n, d));
		d -= 1;
	}
	if (max)
		output[ft_strlen(output) - 1] += 1;
	return (output);
}
