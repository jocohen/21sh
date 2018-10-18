/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:37:07 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:42:39 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	x = 0;
	while (s1[x])
		x += 1;
	while (s2[y] && y < n)
	{
		s1[x] = s2[y];
		x += 1;
		y += 1;
	}
	s1[x] = 0;
	return (s1);
}
