/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefixstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:43:23 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/29 17:36:42 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_prestr(char **output, const char *str, size_t x)
{
	char	*tmp;
	size_t	y;

	y = 0;
	tmp = 0;
	if (!(*output))
	{
		if (!((*output) = ft_strdup(str)))
			return (0);
		return (1);
	}
	if (!(tmp = ft_memalloc(x + ft_strlen(*output) + 1)))
		return (0);
	ft_strcpy((tmp + x), *output);
	while (y < x)
	{
		tmp[y] = str[y];
		y += 1;
	}
	ft_memdel((void **)output);
	(*output) = tmp;
	return (1);
}

int		ft_prechar(char **output, int c, size_t s)
{
	char	*tmp;

	tmp = 0;
	if (*output)
	{
		if (!(tmp = ft_memalloc(s + ft_strlen(*output) + 1)))
			return (0);
		ft_memset(tmp, c, s);
		ft_strcpy((tmp + s), *output);
		ft_memdel((void **)output);
		*output = tmp;
		return (1);
	}
	if (!((*output) = ft_memalloc(s + 1)))
		return (0);
	ft_memset(*output, c, s);
	return (1);
}
