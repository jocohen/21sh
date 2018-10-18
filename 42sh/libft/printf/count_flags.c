/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 03:17:01 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/08 18:09:25 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		cond(size_t *x, size_t *y, const char *input)
{
	if (input[*x] == 's' || input[*x] == 'o' || input[*x] == 'u'
			|| input[*x] == 'x' || input[*x] == 'X' || input[*x] == 'c'
			|| input[*x] == '%' || input[*x] == 'S' || input[*x] == 'C'
			|| input[*x] == 'O' || input[*x] == 'U')
	{
		*y += 1;
		return (1);
	}
	else if (input[*x] == 'p' || input[*x] == 'D' || input[*x] == 'O'
			|| input[*x] == 'U' || input[*x] == 'd' || input[*x] == 'i')
	{
		*y += 2;
		return (1);
	}
	else if (input[*x] == 'h' || input[*x] == 'l' || input[*x] == 'j'
			|| input[*x] == 'z' || input[*x] == '.' || input[*x] == '#'
			|| input[*x] == '-' || input[*x] == ' ' || input[*x] == '+'
			|| (input[*x] >= '0' && input[*x] <= '9'))
	{
		*x += 1;
		*y += 1;
		return (0);
	}
	return (-1);
}

int		count_flags(const char *input, size_t x, char **flags)
{
	size_t	y;
	int		w;

	y = 0;
	x += 1;
	while (input[x])
		if ((w = cond(&x, &y, input)) == -1)
			return (x);
		else if (w)
			break ;
	if (!input[x])
		return (x);
	if (!((*flags) = ft_memalloc(y + 1)))
		return (-1);
	return (-2);
}
