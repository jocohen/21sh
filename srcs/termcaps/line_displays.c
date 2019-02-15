/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_displays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:24:09 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/15 18:10:34 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	delete_line_pos(t_buf *input, t_env **lst)
{
	int		x;

	tputs(tgetstr("cr", 0), 1, ft_writestdin);
	while (input->pos.l)
	{
		tputs(tgetstr("up", 0), 1, ft_writestdin);
		input->pos.l -= 1;
	}
	tputs(tgetstr("cd", 0), 1, ft_writestdin);
	caller_display(*lst, input, 0);
	write_str(input->s, 0);
	x = display_sizing(0) + ft_strlen(input->s);
	input->pos.l = x / window_width_size();
	input->pos.c = x % window_width_size();
	check_last_char_column(input);
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
	write_str(output, 0);
	ft_memdel((void **)&output);
}

void	redisplay_line_selec(t_buf *selec, t_buf *input, t_env **lst)
{
	t_cursor	prev;
	int			x;

	if (!selec->s || !selec->s[0])
	{
		reactualize_output(input, lst);
		return ;
	}
	prev.c = input->pos.c;
	prev.l = input->pos.l;
	tputs(tgetstr("cr", 0), 1, ft_writestdin);
	while (input->pos.l)
	{
		tputs(tgetstr("up", 0), 1, ft_writestdin);
		input->pos.l -= 1;
	}
	tputs(tgetstr("cd", 0), 1, ft_writestdin);
	caller_display(*lst, input, 0);
	display_spe_line(selec, input);
	x = display_sizing(0) + ft_strlen(input->s);
	input->pos.l = x / window_width_size();
	input->pos.c = x % window_width_size();
	check_last_char_column(input);
	replace_cursor(input, prev.c, prev.l);
}
