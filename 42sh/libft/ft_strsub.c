/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:42:54 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:44:21 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	x;

	if (!s)
		return (0);
	x = 0;
	if (!(output = ft_strnew(len)))
		return (0);
	while (x < len)
	{
		output[x] = s[start];
		x += 1;
		start += 1;
	}
	return (output);
}
