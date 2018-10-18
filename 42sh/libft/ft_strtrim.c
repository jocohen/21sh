/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:59:24 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:44:42 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*trim(size_t x, size_t len, char *output, char const *s)
{
	size_t	y;

	y = 0;
	while (x < len + 1 && len)
	{
		output[y] = s[x];
		x += 1;
		y += 1;
	}
	output[y] = 0;
	return (output);
}

char		*ft_strtrim(char const *s)
{
	char	*output;
	size_t	len;
	size_t	x;
	size_t	y;

	if (!s)
		return (0);
	x = 0;
	while (s[x] == ' ' || s[x] == '\n' || s[x] == '\t')
		x += 1;
	y = x;
	while (s[y])
		y += 1;
	len = y - 1;
	while (len && (s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len -= 1;
	if (!((!len) ? (output = ft_strnew(0)) :
				(output = ft_strnew((len - x) + 1))))
		return (0);
	return (trim(x, len, output, s));
}
