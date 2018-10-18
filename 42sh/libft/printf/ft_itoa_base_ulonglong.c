/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ulonglong.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 08:31:24 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:09:42 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_itoa_base_ulonglong(unsigned long long nb, const char *base)
{
	int					x;
	char				*s;
	unsigned long long	num;
	int					base_len;

	x = 1;
	s = 0;
	num = nb;
	base_len = ft_strlen(base);
	while ((num = num / base_len) != 0)
		x += 1;
	if (base_len < 2 || !(s = ft_memalloc(x + 1)))
		return (0);
	x = 0;
	(!nb) ? s[0] = '0' : x;
	while (nb)
	{
		s[x++] = base[nb % base_len];
		nb = nb / base_len;
	}
	ft_strrev(s);
	return (s);
}
