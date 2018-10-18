/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:23:42 by jocohen           #+#    #+#             */
/*   Updated: 2018/02/23 14:47:45 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int				ft_atoi_base(const char *s, int b)
{
	int		x;
	int		base;
	int		num;

	x = ft_strlen(s) - 1;
	base = 1;
	num = 0;
	while (x >= 0)
		if (s[x] >= '0' && s[x] <= '9')
		{
			num = num + (s[x--] - '0') * base;
			base = base * b;
		}
		else if (s[x] >= 'a' && s[x] <= 'f')
		{
			num = num + ((s[x--] - 'a') + 10) * base;
			base = base * b;
		}
		else
			return (-1);
	return (num);
}
