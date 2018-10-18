/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:08:34 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:42:20 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		output[x] = f(s[x]);
		x += 1;
	}
	output[x] = 0;
	return (output);
}
