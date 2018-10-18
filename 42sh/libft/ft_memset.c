/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:21:45 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:33:51 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	x;
	unsigned char	*b_c;

	b_c = (unsigned char *)b;
	x = 0;
	while (x < len)
	{
		b_c[x] = c;
		x += 1;
	}
	return (b);
}
