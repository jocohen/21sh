/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:50:46 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:43:35 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		x;

	x = ft_strlen(s) - 1;
	if (c == 0)
		return ((char *)s + x + 1);
	while (x >= 0)
	{
		if (s[x] == c)
			return ((char *)s + x);
		x -= 1;
	}
	return (NULL);
}
