/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:22:38 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:32:39 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	x;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	x = 0;
	while (x < n)
	{
		d[x] = s[x];
		if (s[x] == (unsigned char)c)
			return (d + (x + 1));
		x += 1;
	}
	return (NULL);
}
