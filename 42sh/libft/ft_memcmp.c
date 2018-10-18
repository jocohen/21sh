/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:52:30 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:32:53 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	x;

	x = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (x < n)
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x += 1;
	}
	return (0);
}
