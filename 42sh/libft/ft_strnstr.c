/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:08:26 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:43:23 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	if (!needle[x])
		return ((char *)haystack);
	while (haystack[x] && x < len)
	{
		y = 0;
		while (haystack[x + y] == needle[y] && (x + y) < len)
		{
			if (!needle[y + 1])
				return ((char *)haystack + (x));
			y += 1;
		}
		x += 1;
	}
	return (NULL);
}
