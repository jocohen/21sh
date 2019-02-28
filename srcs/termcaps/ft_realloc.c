/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:41:58 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/28 17:22:38 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_realloc(char **ptr, size_t size, size_t len)
{
	char	*tmp;

	if (!(tmp = ft_memalloc(size)))
		ft_exit_malloc();
	tmp = ft_memcpy(tmp, *ptr, len);
	ft_memdel((void **)ptr);
	*ptr = tmp;
}
