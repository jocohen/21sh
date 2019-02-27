/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:54:39 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/27 15:17:15 by jonascohen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char	*dst_char;
	char	*src_char;

	i = 0;
	dst_char = (char *)dst;
	src_char = (char *)src;
	while (i < n)
	{
		dst_char[i] = src_char[i];
		i += 1;
	}
	return (dst_char);
}
