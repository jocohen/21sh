/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:39:51 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:40:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i_d;
	size_t	i_s;
	size_t	sub_i;

	sub_i = 0;
	i_s = ft_strlen(src);
	i_d = ft_strlen(dst);
	if (size <= i_d)
		return (size + i_s);
	i_s += i_d;
	size = size - (i_d + 1);
	while (size && src[sub_i])
	{
		dst[i_d] = src[sub_i];
		i_d += 1;
		sub_i += 1;
		size--;
	}
	dst[i_d] = 0;
	return (i_s);
}
