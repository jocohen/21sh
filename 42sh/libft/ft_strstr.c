/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:54:54 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:44:04 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	x;
	size_t	y;

	x = 0;
	if (!needle[x])
		return ((char *)haystack);
	while (haystack[x])
	{
		y = 0;
		while (haystack[x + y] == needle[y])
		{
			if (!needle[y + 1])
				return ((char *)haystack + (x));
			y += 1;
		}
		x += 1;
	}
	return (NULL);
}
