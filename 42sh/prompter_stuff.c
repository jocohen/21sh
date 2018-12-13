/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:18:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/11 17:55:45 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

// void	write_log(t_buf input)
// {
// 	int fd;
//
// 	fd = open("/Users/jocohen/Documents/42_saves/42sh/log", O_WRONLY);
// 	ft_putstr_fd(": colum :", fd);
// 	ft_putstr_fd(ft_itoa(input.pos.c), fd);
// 	ft_putstr_fd(": line :", fd);
// 	ft_putstr_fd(ft_itoa(input.pos.l), fd);
// 	ft_putstr_fd(": colum window size :", fd);
// 	ft_putstr_fd(ft_itoa(window_width_size()), fd);
// 	ft_putstr_fd(": index :", fd);
// 	ft_putstr_fd(ft_itoa(input.x), fd);
// 	ft_putstr_fd(":       ", fd);
// 	ft_putstr_fd(, fd);
// 	close(fd);
// }

void	input_character(t_buf *input, char k)
{
	tputs(tgetstr("im", 0), 1, ft_writestdin);
	write(1, &k, 1);
	if (input->pos.c + 1 == (size_t)window_width_size())
	{
		input->pos.l += 1;
		write(1, "c", 1);
		input->pos.c = 1;
		cursor_movement(input, -2);
		tputs(tgetstr("dc", 0), 1, ft_writestdin);
	}
	else
		input->pos.c += 1;
	tputs(tgetstr("ei", 0), 1, ft_writestdin);
}

void	check_over_buffer(t_buf *input, char *into_buff)
{
	if (!into_buff)
	{
		if (ft_strlen(input->s) == input->buf_size - 1)
		{
			if (!(input->s = ft_realloc(input->s, input->buf_size + 128,
				input->buf_size)))
				ft_exit(0);
			input->buf_size += 128;
		}
		return ;
	}
	while (input->buf_size - 1 < ft_strlen(into_buff))
	{
		if (!(input->s = ft_realloc(input->s, input->buf_size + 128,
			input->buf_size)))
			ft_exit(0);
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
