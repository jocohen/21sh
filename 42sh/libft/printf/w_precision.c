/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_precision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:42:36 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:36 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	w_precision(wchar_t *insert, int precision)
{
	size_t	x;
	size_t	size;

	x = 0;
	size = 0;
	while (insert[x])
	{
		size += ft_lenbyte(insert[x]);
		if (precision < (int)size)
			break ;
		x += 1;
	}
	while (insert[x])
		insert[x++] = 0;
}
