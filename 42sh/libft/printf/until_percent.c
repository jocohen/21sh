/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:10:31 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:11:30 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		until_percent(const char *input, size_t *x, char **display)
{
	size_t	y;
	size_t	q;

	q = 0;
	*display = 0;
	y = *x;
	while (input[*x])
	{
		if (input[*x] == '%')
			break ;
		*x += 1;
	}
	if (*x - y != 0)
	{
		if (!((*display) = ft_memalloc((*x - y) + 1)))
			return (0);
		while (*x > y)
			(*display)[q++] = input[y++];
	}
	if (!(input[*x]))
		return (1);
	return (2);
}
