/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:53:20 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/29 17:33:07 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long	captain_2(t_out_s s, t_str in, t_beflags f, long y)
{
	f.field = y - (ft_strlen(s.insert) + ft_strlen(s.output));
	if (f.field > 0)
	{
		if (!f.minus && (!f.zero || (f.precision > -1 && in.flags[0] != '%'
		&& in.flags[0] != 'c' && in.flags[0] != 's')))
			if (!(ft_prechar(&s.output, ' ', f.field)))
				return (-1);
	}
	y = (ft_strlen(s.output) + ft_strlen(s.insert) + ft_strlen(s.end_fl));
	(!s.insert[0] && in.flags[0] == 'c') ? y += 1 : y;
	ft_putstr(in.display);
	ft_putstr(s.output);
	if (s.insert[0] || in.flags[0] == 'c')
		ft_putstr(s.insert);
	ft_putstr(s.end_fl);
	ft_memdel((void **)&s.output);
	ft_memdel((void **)&s.end_fl);
	return (y);
}
