/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:24:09 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/28 15:44:24 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	cut_selection(t_buf *input, t_buf *selec)
{
	size_t	x;

	x = 0;
	if (!selec->s || !selec->s[0])
		return ;
	if (!selec->pos.l && (int)selec->pos.c == -1)
		x = input->x + 1;
	else if (selec->pos.c == 1)
		x = input->x - selec->x;
	ft_memmove(input->s + x, input->s + x + selec->x,
		(ft_strlen(input->s) - (x + selec->x) + 1));
	if (selec->pos.c == 1)
	{
		while (selec->x)
		{
			cursor_movement(input, -1);
			selec->x -= 1;
		}
	}
	(input->s[input->x]) ? cursor_movement(input, 1) : 0;
	selec_buffer(0, input);
}

void	paste_intra_clip(t_buf *input)
{
	size_t	x;

	if (!g_clip)
		return ;
	while (input->buf_size - 1 < ft_strlen(input->s) + ft_strlen(g_clip))
	{
		if (!(input->s = ft_realloc(input->s, input->buf_size + 128,
			input->buf_size)))
			ft_exit(0);
		input->buf_size += 128;
	}
	ft_memmove(input->s + input->x + ft_strlen(g_clip), input->s + input->x,
		ft_strlen(input->s) - input->x);
	ft_memcpy(input->s + input->x, g_clip, ft_strlen(g_clip));
	x = ft_strlen(g_clip) + 1;
	while (--x)
		cursor_movement(input, 1);
	reactualize_output(input);
}

void	display_spe_line(t_buf *selec, t_buf *input)
{
	char	*output;
	size_t	x;

	x = 0;
	if (!(output = ft_memalloc(ft_strlen(input->s) + ft_strlen(ANSI_DARK_GRAY)
		+ ft_strlen(ANSI_DEF_BG) + 1)))
		ft_exit(0);
	if (!selec->pos.l && (int)selec->pos.c == -1)
		x = input->x + 1;
	else if (selec->pos.c == 1)
		x = input->x - selec->x;
	ft_memcpy(output, input->s, x);
	ft_strcat(ft_strcat(ft_strcat(ft_strcat(output, ANSI_DARK_GRAY), selec->s),
		ANSI_DEF_BG), input->s + x + selec->x);
	write(1, output, ft_strlen(output));
	ft_memdel((void **)&output);
}

void	redisplay_line_selec(t_buf *selec, t_buf *input)
{
	t_cursor	prev;
	int			x;

	if (!selec->s || !selec->s[0])
	{
		reactualize_output(input);
		return ;
	}
	prev.c = input->pos.c;
	prev.l = input->pos.l;
	x = display_sizing(0);
	input->pos.c = 0;
	tputs(tgetstr("cr",	0), 1, ft_writestdin);
	while (input->pos.l)
	{
		tputs(tgetstr("up",	0), 1, ft_writestdin);
		input->pos.l -= 1;
	}
	while (x)
	{
		cursor_movement(input, 2);
		x -= 1;
	}
	tputs(tgetstr("cd",	0), 1, ft_writestdin);
	display_spe_line(selec, input);
	x = display_sizing(0) + ft_strlen(input->s);
	input->pos.l = x / window_width_size();
	input->pos.c = x % window_width_size();
	check_last_char_column(input);
	replace_cursor(input, prev.c, prev.l);
}

t_buf	*selec_buffer(int t, t_buf *input)
{
	static t_buf	selection;

	if (t)
		return (&selection);
	else
	{
		reactualize_output(input);
		ft_memdel((void **)&(selection.s));
		return (0);
	}
}

void	selection_init(t_buf *input, int dir)
{
	t_buf	*selec;

	selec = selec_buffer(1, 0);
	if (!selec->s)
	{
		selec->buf_size = 64;
		if (!(selec->s = ft_memalloc(selec->buf_size)))
			ft_exit(0);
		selec->x = 0;
		selec->pos.l = 0;
	}
	else
		check_over_buffer(selec, 0);
	if (!selec->s[0])
		selec->pos.c = dir;
	if ((size_t)dir != selec->pos.c)
	{
		(!selec->pos.l) ? cursor_movement(input, dir) : 0;
		selec->x -= 1;
		selec->pos.l = 0;
		if (dir == -1)
			selec->s[selec->x] = 0;
		else if (dir == 1)
			ft_memmove(selec->s, selec->s + 1, selec->x + 1);
		if (!selec->x)
			ft_memdel((void **)&(selec->s));
		redisplay_line_selec(selec, input);
		return ;
	}
	if (!input->s[input->x] || selec->pos.l == 1)
	{
		if (dir == -1)
			(input->x) ? cursor_movement(input, -1) : 0;
		return ;
	}
	if (dir == -1 && selec->pos.l != 1)
	{
		ft_memmove(selec->s + 1, selec->s, selec->x);
		selec->s[0] = input->s[input->x];
		selec->x += 1;
		(!input->x) ? selec->pos.l = 1 : 0;
		(input->x) ? cursor_movement(input, -1) : 0;
	}
	else if (dir == 1)
	{
		selec->s[selec->x++] = input->s[input->x];
		cursor_movement(input, 1);
	}
	selec->pos.c = dir;
	redisplay_line_selec(selec, input);
}
