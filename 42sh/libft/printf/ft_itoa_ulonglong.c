/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ulonglong.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 07:50:55 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:10:03 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		digit(unsigned long long n, size_t x)
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

static size_t	n_digit(unsigned long long n)
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

char			*ft_itoa_ulonglong(unsigned long long n)
{
	size_t	d;
	char	*output;

	d = n_digit(n);
	if (!(output = ft_strnew(d)))
		return (0);
	while (d)
	{
		output = ft_strcatc(output, digit(n, d));
		d -= 1;
	}
	return (output);
}
