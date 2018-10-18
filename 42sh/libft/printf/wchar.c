/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:46:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:43 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

wchar_t		*sea_wc(va_list *arg_ft, t_var every)
{
	wchar_t	*insert;
	size_t	y;

	insert = 0;
	y = 0;
	every.lc = va_arg(*arg_ft, wint_t);
	(!every.lc) ? y += 1 : y;
	if (!(insert = ft_memalloc(sizeof(wchar_t) * (2 - y))))
		return (0);
	insert[0] = every.lc;
	if (!(print_local(insert)))
	{
		ft_memset(insert, 0, 2 - y);
		ft_memdel((void **)&insert);
		return (0);
	}
	return (insert);
}
