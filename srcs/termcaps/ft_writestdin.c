/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writestdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:33:57 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/15 18:06:06 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_writestdin(int c)
{
	write(0, &c, 1);
	return (0);
}

void	write_str(char *s, int c)
{
	size_t		size;

	size = 1;
	if (!c)
		size = ft_strlen(s);
	if (isatty(1))
		write(1, s, size);
	else if (isatty(2))
		write(2, s, size);
}
