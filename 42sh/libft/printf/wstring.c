/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:29:07 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

wchar_t		*sea_ws(va_list *arg_ft, t_var every)
{
	size_t	x;
	wchar_t	*insert;

	x = 0;
	insert = 0;
	if (!(every.ls = va_arg(*arg_ft, wchar_t *)))
		every.ls = L"(null)";
	if (!(insert = ft_memalloc(sizeof(wchar_t) * (ft_wstrlen(every.ls) + 1))))
		return (0);
	while (every.ls[x])
	{
		insert[x] = every.ls[x];
		x += 1;
	}
	return (insert);
}
