/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:18:48 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/28 17:28:15 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	input_character(t_buf *input, char k)
{
	put_term_rout("im");
	write_str(&k, 1);
	if (input->pos.c + 1 == (size_t)window_width_size())
	{
		input->pos.l += 1;
		write_str("c", 0);
		input->pos.c = 1;
		cursor_movement(input, -2);
		put_term_rout("dc");
	}
	else
		input->pos.c += 1;
	put_term_rout("ei");
}

void	check_over_buffer(t_buf *input, char *into_buff)
{
	size_t x;

	x = ft_strlen(input->s);
	if (!into_buff)
	{
		if (ft_strlen(input->s) == input->buf_size - 1)
		{
			ft_realloc(&(input->s), input->buf_size + 128, input->buf_size);
			input->buf_size += 128;
		}
		return ;
	}
	while (input->buf_size - 1 < ft_strlen(into_buff))
	{
		ft_realloc(&(input->s), input->buf_size + 128, input->buf_size);
		input->buf_size += 128;
	}
}

void	u8_buff(t_buf *input, size_t len)
{
	size_t x;

	x = ft_strlen(input->s);
	while (input->buf_size - 1 < ft_strlen(input->s) + len)
	{
		ft_realloc(&(input->s), input->buf_size + 128, input->buf_size);
		input->buf_size += 128;
	}
}

char	check_prev_read(char k)
{
	static char		c[2];

	if (k && k != -1)
	{
		if (c[0] == 27 && k == -6)
		{
			c[0] = -6;
			return (c[1]);
		}
		c[1] = c[0];
		c[0] = k;
	}
	return (c[1]);
}
