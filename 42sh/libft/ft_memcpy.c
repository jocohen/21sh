/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:19:41 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:33:11 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	x;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	x = 0;
	while (x < n)
	{
		d[x] = s[x];
		x += 1;
	}
	return (d);
}
