/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:33:54 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:43:12 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*output;

	if (!(output = (char *)malloc(size + 1)))
		return (0);
	while ((size + 1))
	{
		output[size] = 0;
		size -= 1;
	}
	return (output);
}
