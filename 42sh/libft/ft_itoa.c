/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:50:50 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:20:13 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		digit(long n, size_t x)
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

static size_t	n_digit(long n)
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

char			*ft_itoa(int n)
{
	long	num;
	size_t	d;
	char	*output;

	num = n;
	d = n_digit(num);
	if (num < 0)
	{
		num = -num;
		if (!(output = ft_strnew(d + 1)))
			return (0);
		output = ft_strcatc(output, '-');
	}
	else
	{
		if (!(output = ft_strnew(d)))
			return (0);
	}
	while (d)
	{
		output = ft_strcatc(output, digit(num, d));
		d -= 1;
	}
	return (output);
}
