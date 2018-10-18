/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 09:40:28 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:09:15 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*sea_c(va_list *arg_ft, t_var every)
{
	char	*insert;
	size_t	y;

	insert = 0;
	every.c = va_arg(*arg_ft, int);
	y = 0;
	(!every.c) ? y = 1 : y;
	if (!(insert = ft_memalloc(2 - y)))
		return (0);
	insert[0] = every.c;
	return (insert);
}
