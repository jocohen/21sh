/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:41:58 by jocohen           #+#    #+#             */
/*   Updated: 2018/06/24 14:24:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	*ft_realloc(void *ptr, size_t size, size_t len)
{
	void	*tmp;

	if (!(tmp = ft_memalloc(size)))
		return (0);
	ft_memcpy(tmp, ptr, len);
	ft_memdel((void **)&ptr);
	return ((void *)tmp);
}