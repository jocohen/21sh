/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_local.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:07:19 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:08 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		print_local(const wchar_t *input)
{
	size_t			x;
	unsigned int	num;
	int				n_bits;

	x = 0;
	while (input[x])
	{
		n_bits = 1;
		num = (unsigned int)input[x];
		if (num >= 0xd800 && num <= 0xdfff)
			return (0);
		if (num > 255)
			while (num /= 2)
				n_bits += 1;
		if (((unsigned int)input[x] <= 255 && MB_CUR_MAX >= 1) ||
		(n_bits > 7 && n_bits <= 11 && MB_CUR_MAX >= 2) ||
		(n_bits > 11 && n_bits <= 16 && MB_CUR_MAX >= 3) ||
		((unsigned int)input[x] <= 0x10ffff && MB_CUR_MAX >= 4))
			x += 1;
		else
			return (0);
	}
	return (1);
}
