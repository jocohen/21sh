/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:47:42 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:36:02 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	x;

	x = 0;
	if (c == 0)
	{
		while (s[x])
			x += 1;
		return ((char *)s + x);
	}
	while (s[x])
	{
		if (s[x] == c)
			return ((char *)s + x);
		x += 1;
	}
	return (0);
}
