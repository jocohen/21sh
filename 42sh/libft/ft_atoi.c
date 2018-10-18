/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:16:04 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/16 18:49:51 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int		atoi_end(const char *s, size_t y, size_t x, int neg)
{
	int		output;

	output = 0;
	while (s[x + y] >= '0' && s[x + y] <= '9')
	{
		output = output * 10 + (s[x + y] - '0');
		x += 1;
	}
	if (x > 10)
		return ((neg > 0) ? -1 : 0);
	return (output * neg);
}

int				ft_atoi(const char *s)
{
	size_t	x;
	size_t	y;
	int		neg;

	if (!s)
		return (0);
	neg = 1;
	x = 0;
	y = 0;
	while (s[y] == 32 || s[y] == 9 || s[y] == 10 ||
			s[y] == 11 || s[y] == 12 || s[y] == 13)
		y += 1;
	if ((s[y] == '-') || (s[y] == '+'))
		y += 1;
	if (s[y - 1] == '-')
		neg = -1;
	while (s[y] == '0')
		y += 1;
	return (atoi_end(s, y, x, neg));
}
