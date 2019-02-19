/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_shift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:47:38 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/19 16:03:44 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

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
	put_term_rout("do");
	put_term_rout("cr");
	input->pos.c = 0;
	input->pos.l += 1;
	while (input->pos.c != x.c)
	{
		put_term_rout("nd");
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
				put_term_rout("nd");
				input->pos.c += 1;
			}
		}
		else
			input->x -= window_width_size();
		input->pos.l -= 1;
		put_term_rout("up");
	}
	else if (direction == 1)
		cursor_one_down(input);
}

size_t	last_nl_pos(t_buf *input)
{
	size_t	x;
	size_t	col;

	col = 0;
	x = input->x - 1;
	while (x >= 0 && input->s[x] != '\n')
	{
		x -= 1;
		col += 1;
	}
	return (col);
}

int		pos_nl(t_buf *input)
{
	size_t	x;

	x = 0;
	
}

void	up_into_final_pos(t_buf *input, int dir)
{
	int		x;

	if (input->s[input->x] == '\n')
	{
		input->pos.c = last_nl_pos(input);
		input->x += 1;
	}
	else
		input->pos.c = window_width_size() - 1;
	input->pos.l -= 1;
	put_term_rout("up");
	x = input->pos.c;
	while (x)
	{
		put_term_rout("nd");
		x -= 1;
	}
}

void	cursor_movement(t_buf *input, int dir)
{
	if (dir <= -1)
	{
		(dir != -2) ? input->x -= 1 : 0;
		if (input->pos.l && !input->pos.c)
			return (up_into_final_pos(input, dir));
		input->pos.c -= 1;
		put_term_rout("le");
	}
	else if (dir >= 1)
	{
		(dir != 2) ? input->x += 1 : 0;
		if (input->pos.c + 1 == (size_t)window_width_size())
		{
			put_term_rout("do");
			put_term_rout("cr");
			input->pos.c = 0;
			input->pos.l += 1;
			return ;
		}
		put_term_rout("nd");
		input->pos.c += 1;
	}
}
