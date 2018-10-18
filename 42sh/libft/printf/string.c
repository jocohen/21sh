/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 04:53:56 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:24 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*sea_s(va_list *arg_ft, t_var every)
{
	char	*insert;

	insert = 0;
	if (!(every.s = va_arg(*arg_ft, char *)))
		every.s = "(null)";
	if (!(insert = ft_strdup(every.s)))
		return (0);
	return (insert);
}
