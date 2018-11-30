/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:18:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/30 16:20:57 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	write_log(t_buf input)
{
	int fd;

	fd = open("/Users/jocohen/Documents/42_saves/42sh/log", O_WRONLY);
	ft_putstr_fd(": colum :", fd);
	ft_putstr_fd(ft_itoa(input.pos.c), fd);
	ft_putstr_fd(": line :", fd);
	ft_putstr_fd(ft_itoa(input.pos.l), fd);
	ft_putstr_fd(": colum window size :", fd);
	ft_putstr_fd(ft_itoa(window_width_size()), fd);
	ft_putstr_fd(": index :", fd);
	ft_putstr_fd(ft_itoa(input.x), fd);
	ft_putstr_fd(":       ", fd);
	// ft_putstr_fd(, fd);
	close(fd);
}

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

void	end_or_keep(t_buf *input, char k, t_list **lst)
{
	size_t	prev_line;

	if (k > 31 && k < 127)
	{
		prev_line = input->pos.l;
		input_character(input, k);
		ft_memmove(input->s + input->x + 1, input->s + input->x,
			ft_strlen(input->s + input->x) + 1);
		input->s[input->x++] = k;
		if (((display_sizing(0) + ft_strlen(input->s)) / window_width_size()) != prev_line)
			reactualize_output(input, lst);
	}
}

void	analyse_input(t_buf *input, char k, t_list **lst, t_historic **history)
{
	if (k == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_writestdin);
		caller_display(*lst, input, 0);
		reactualize_output(input, lst);
	}
	else if (k == 27)
		escape_analysis(input, history, lst);
	else if (k == 4 || (k == 127 && input->x))
	{
		(k == 4) ? del_char(input, 1, lst) : 0;
		(k == 127) ? del_char(input, 0, lst) : 0;
	}
	else
		end_or_keep(input, k, lst);
}

char	*prompt(t_list **lst, t_historic **history)
{
	t_buf		input;
	char		k;
	int			stdin_cpy;

	input.buf_size = 128;
	if (!(input.s = ft_memalloc(input.buf_size)))
		ft_exit(0);
	input.x = 0;
	caller_display(*lst, &input, 1);
	stdin_cpy = dup(0);
	while (1)
	{
		check_over_buffer(&input, 0);
		if (read(0, &k, 1) == -1)
		{
			if (!g_pid && !g_resize)
				ft_exit(0);
			k = -1;
			dup2(stdin_cpy, 0);
			if (g_pid == 1 && recall_prompt(0, 0, -1))
			{
				ft_memdel((void **)&input.s);
				return (enter_section(&input, lst, history, -1));
			}
			(g_pid == 1) ? enter_section(&input, lst, history, 1) : 0 ;
			(g_resize == 1) ? check_resize_curs_pos(&input) : 0;
			g_pid = 0;
			g_resize = 0;
		}
		check_prev_read(k);
		(k != 27 && k != -1) ? selec_buffer(0, &input, lst) : 0;
		if (k == 4 && !input.s[0] && !recall_prompt(0, 0, -1))
		{
			tputs(tgetstr("do", 0), 1, ft_writestdin);
			tputs(tgetstr("cr",	0), 1, ft_writestdin);
			lst_deletion(lst);
			ft_memdel((void **)&input.s);
			break ;
		}
		if (k == 10)
		{
			if (recall_prompt(0, 0, -1))
				return (enter_section(&input, lst, history, -1));
			enter_section(&input, lst, history, 0);
		}
		else
			analyse_input(&input, k, lst, history);
	}
	return (0);
}
