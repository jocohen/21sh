/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:16:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:42:55 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (src[x] && x < len)
	{
		dst[x] = src[x];
		x += 1;
	}
	y = x;
	if (x != len)
		dst[x] = 0;
	while (!src[y] && x < len)
	{
		dst[x] = 0;
		x += 1;
	}
	return (dst);
}
