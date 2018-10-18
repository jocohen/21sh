/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:25:05 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:32:45 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*output;
	unsigned int	x;

	x = 0;
	output = (unsigned char *)s;
	while (x < n)
	{
		if (output[x] == (unsigned char)c)
			return (output + x);
		x += 1;
	}
	return (NULL);
}
