/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:18:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/14 16:51:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	write_log(t_buf input)
{
	int fd;
	fd = open("/Users/jocohen/Documents/42_saves/42sh/log", O_WRONLY, O_APPEND);
	ft_putstr_fd(": colum :", fd);
	ft_putstr_fd(ft_itoa(input.pos.c), fd);
	ft_putstr_fd(": line :", fd);
	ft_putstr_fd(ft_itoa(input.pos.l), fd);
	ft_putstr_fd(": widsize col :", fd);
	ft_putstr_fd(ft_itoa(window_width_size()), fd);
	ft_putstr_fd(": totalc:", fd);
	ft_putstr_fd(ft_itoa(display_sizing(0) + ft_strlen(input.s)), fd);
	ft_putstr_fd(": ind : ", fd);
	ft_putstr_fd(ft_itoa(input.x), fd);
	ft_putstr_fd(" :", fd);
	close(fd);
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

void	end_or_keep(t_buf *input, char k, t_list **lst, t_historic **history)
{
	if (k > 31 && k < 127)
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
		ft_memmove(input->s + input->x + 1, input->s + input->x,
			ft_strlen(input->s + input->x) + 1);
		input->s[input->x++] = k;
		tputs(tgetstr("ei", 0), 1, ft_writestdin);
	}
	else if (k == 10)
		enter_section(input, lst, history, 0);
}

void	analyse_input(t_buf *input, char k, t_list **lst, t_historic **history)
{
	if (k == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_writestdin);
		caller_display(*lst, input);
	}
	else if (k == 27)
	{
		escape_analysis(input, history);
		return ;
	}
	else if (k == 4 || (k == 127 && input->x))
	{
		(k == 4) ? del_char(input, 1) : 0;
		(k == 127) ? del_char(input, 0) : 0;
	}
	else
		end_or_keep(input, k, lst, history);
}

void	prompt(t_list **lst, t_historic **history)
{
	t_buf		input;
	char		k;
	int			stdin_cpy;

	input.buf_size = 128;
	if (!(input.s = ft_memalloc(input.buf_size)))
		ft_exit(0);
	input.x = 0;
	caller_display(*lst, &input);
	stdin_cpy = dup(0);
	while (1)
	{
		check_over_buffer(&input, 0);
		write_log(input);
		if (read(0, &k, 1) == -1)
		{
			k = -1;
			if (g_pid == 1)
			{
				dup2(stdin_cpy, 0);
				enter_section(&input, lst, history, 1);
				g_pid = 0;
			}
			else if (g_resize == 1)
			{
				dup2(stdin_cpy, 0);
				g_resize = 0;
				check_resize_curs_pos(&input);
			}
			else
				ft_exit(0);
		}
		check_prev_read(k);
		if (k == 4 && !input.s[0])
		{
			tputs(tgetstr("do", 0), 1, ft_writestdin);
			lst_deletion(lst);
			ft_memdel((void **)&input.s);
			break ;
		}
		if (k != -1)
			analyse_input(&input, k, lst, history);
	}
}
