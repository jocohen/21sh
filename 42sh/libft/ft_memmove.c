/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:50:10 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:33:45 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			x;

	x = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == s)
		return (d);
	if (s > d)
		while (x < len)
		{
			d[x] = s[x];
			x += 1;
		}
	else
	{
		x = len;
		while ((int)x > 0)
		{
			d[x - 1] = s[x - 1];
			x -= 1;
		}
	}
	return (d);
}
