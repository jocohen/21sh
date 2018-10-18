/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:13:18 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:42:28 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	x;
	char	*output;

	if (!s)
		return (0);
	x = ft_strlen(s);
	if (!(output = ft_strnew(x)))
		return (0);
	x = 0;
	while (s[x])
	{
		output[x] = f(x, s[x]);
		x += 1;
	}
	output[x] = 0;
	return (output);
}
