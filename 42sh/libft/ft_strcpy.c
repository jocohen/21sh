/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:13:07 by jocohen           #+#    #+#             */
/*   Updated: 2018/02/20 11:18:07 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int		x;

	x = 0;
	if (!src)
		return (dst);
	while (src[x])
	{
		dst[x] = src[x];
		x += 1;
	}
	dst[x] = 0;
	return (dst);
}
