/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:12:34 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/05 14:45:21 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	x;

	if ((!s1 && s2) || (!s2 && s1))
		return (-1);
	if (!s1 && !s2)
		return (0);
	x = 0;
	while (s1[x] == s2[x] && s1[x] && s2[x])
		x += 1;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
