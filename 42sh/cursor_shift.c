/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_shift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:47:38 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/11 18:52:40 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	cursor_one_down(t_buf *input)
{
	t_cursor	x;

	x.c = (display_sizing(0) + ft_strlen(input->s)) % window_width_size();
	x.l = (display_sizing(0) + ft_strlen(input->s)) / window_width_size();
	if (input->pos.l == x.l)
		return ;
	input->x += window_width_size();
	if (x.l == input->pos.l + 1 && input->pos.c > x.c)
		input->x = ft_strlen(input->s);
	else
		x.c = input->pos.c;
	tputs(tgetstr("do", 0), 1, ft_writestdin);
	tputs(tgetstr("cr", 0), 1, ft_writestdin);
	input->pos.c = 0;
	input->pos.l += 1;
	while (input->pos.c != x.c)
	{
		tputs(tgetstr("nd", 0), 1, ft_writestdin);
		input->pos.c += 1;
	}
}

void	vertical_cursor(t_buf *input, int direction)
{
	if (direction == -1 && input->pos.l)
	{
		if (input->pos.c <= (size_t)display_sizing(0) && input->pos.l == 1)
		{
			input->x = 0;
			while (input->pos.c != (size_t)display_sizing(0))
			{
				tputs(tgetstr("nd", 0), 1, ft_writestdin);
				input->pos.c += 1;
			}
		}
		else
			input->x -= window_width_size();
		input->pos.l -= 1;
		tputs(tgetstr("up", 0), 1, ft_writestdin);
	}
	else if (direction == 1)
		cursor_one_down(input);
}

void	up_into_final_pos(t_buf *input)
{
	int		x;

	input->pos.c = window_width_size() - 1;
	input->pos.l -= 1;
	tputs(tgetstr("up", 0), 1, ft_writestdin);
	x = window_width_size() - 1;
	while (x)
	{
		tputs(tgetstr("nd", 0), 1, ft_writestdin);
		x -= 1;
	}
}

void	cursor_movement(t_buf *input, int dir)
{
	if (dir <= -1)
	{
		(dir != -2) ? input->x -= 1 : 0;
		if (input->pos.l && !input->pos.c)
			return (up_into_final_pos(input));
		input->pos.c -= 1;
		tputs(tgetstr("le", 0), 1, ft_writestdin);
	}
	else if (dir >= 1)
	{
		(dir != 2) ? input->x += 1 : 0;
		if (input->pos.c + 1 == (size_t)window_width_size())
		{
			tputs(tgetstr("do", 0), 1, ft_writestdin);
			tputs(tgetstr("cr", 0), 1, ft_writestdin);
			input->pos.c = 0;
			input->pos.l += 1;
			return ;
		}
		tputs(tgetstr("nd", 0), 1, ft_writestdin);
		input->pos.c += 1;
	}
}
