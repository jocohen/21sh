/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 02:02:07 by jocohen           #+#    #+#             */
/*   Updated: 2018/02/27 15:16:40 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*end(int nb, char *s, const char *base, int base_len)
{
	int		x;

	x = 0;
	while (nb)
	{
		s[x++] = base[nb % base_len];
		nb = nb / base_len;
	}
	ft_strrev(s);
	return (s);
}

char		*ft_itoa_base(int nb, const char *base)
{
	int		x;
	char	*s;
	int		num;
	int		base_len;

	x = 1;
	num = nb;
	base_len = ft_strlen(base);
	while (num /= base_len)
		x += 1;
	if (base_len < 2 || base_len > 16 || !(s = ft_memalloc(x + 1)))
		return (0);
	x = 0;
	(!nb) ? s[x] = '0' : x;
	if (nb < 0)
		(base_len == 10) ? s[x++] = '-' : x;
	(nb < 0) ? nb *= -1 : nb;
	return (end(nb, s, base, base_len));
}
