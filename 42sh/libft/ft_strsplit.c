/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:16:11 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:43:54 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char		**fill_and_mem(char const *s, char c, char **output,
		unsigned int n)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	l;

	l = 0;
	x = 0;
	while (s[x])
	{
		y = 0;
		while (s[x + y] != c && s[x + y] && l != n)
		{
			if (s[(x + y) + 1] == c || !(s[(x + y) + 1]) || !s[x + y])
			{
				if (!(*(output + l) = ft_strnew(y + 1)))
					return (0);
				ft_memcpy(output[l], s + x, y + 1);
				l += 1;
			}
			y += 1;
		}
		x += (y + 1);
	}
	output[l] = 0;
	return (output);
}

static size_t	count_n(char const *s, char c)
{
	unsigned int	x;
	size_t			n;

	n = 0;
	x = 0;
	while (s[x])
	{
		if ((s[x + 1] == c || !s[x + 1]) && s[x] != c)
			n += 1;
		x += 1;
	}
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**output;
	size_t			n;

	if (!s)
		return (0);
	n = count_n(s, c);
	if (!(output = (char **)malloc(sizeof(char *) * (n + 1))))
		return (0);
	return (fill_and_mem(s, c, output, n));
}
