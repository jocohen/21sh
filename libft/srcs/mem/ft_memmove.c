/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:33:19 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/21 13:29:53 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (s == dst)
		return (d);
	if (s < d)
	{
		i = len;
		while ((int)i > 0)
		{
			d[i - 1] = s[i - 1];
			i -= 1;
		}
	}
	else
		while (i < len)
		{
			d[i] = s[i];
			i += 1;
		}
	return (d);
}
