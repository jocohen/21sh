/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:33:50 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/23 14:09:23 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		x;
	int		y;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return (s1);
	y = 0;
	x = 0;
	while (s1[x])
		x += 1;
	while (s2[y])
	{
		s1[x] = s2[y];
		x += 1;
		y += 1;
	}
	s1[x] = 0;
	return (s1);
}
