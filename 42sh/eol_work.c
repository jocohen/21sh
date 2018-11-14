/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eol_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:58:55 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/05 13:06:04 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		first_resize(int x)
{
	static int	s;

	if (x == -2)
	{
		s = 0;
		return (0);
	}
	else if (x == -1)
		return (s);
	s = x;
	return (0);
}

void	del_tarace(t_buf *input)
{
	size_t		ind;

	input->pos.l = (display_sizing(0) + ft_strlen(input->s) - 1) / window_width_size();
	if (first_resize(-1) == 0 && input->pos.l)
	{
		input->pos.l += 1;
		first_resize(1);
	}
	if (!input->s[input->x] && input->pos.l && !input->pos.c)
		input->pos.l -= 1;
	ind = input->x;
	input->x = ft_strlen(input->s);
	delete_line_pos(input);
	while (ind < input->x)
		cursor_movement(input, -1);

}

void	check_resize_curs_pos(t_buf *input)
{
	size_t	x;

	// if (input->pos.l)
	// {
		// del_tarace(input);
		// return ;
	// }
	x = display_sizing(0) + input->x;
	input->pos.l = x / window_width_size();
	input->pos.c = x % window_width_size();
}

void	cursor_movement(t_buf *input, int dir)
{
	int		x;

	if (dir <= -1)
	{
		(dir != -2) ? input->x -= 1 : 0;
		if (input->pos.l && !input->pos.c)
		{
			input->pos.c = window_width_size() - 1;
			input->pos.l -= 1;
			tputs(tgetstr("up", 0), 1, ft_writestdin);
			x = window_width_size() - 1;
			while (x)
			{
				tputs(tgetstr("nd", 0), 1, ft_writestdin);
				x -= 1;
			}
			return ;
		}
		input->pos.c -= 1;
		tputs(tgetstr("le", 0), 1, ft_writestdin);
	}
	else if (dir >= 1)
	{
		(dir != 2) ? input->x += 1 : 0;
		if (input->pos.c + 1 == (size_t)window_width_size())
		{
			tputs(tgetstr("do",	0), 1, ft_writestdin);
			tputs(tgetstr("cr",	0), 1, ft_writestdin);
			input->pos.c = 0;
			input->pos.l += 1;
			return ;
		}
		tputs(tgetstr("nd", 0), 1, ft_writestdin);
		input->pos.c += 1;
	}
}

void	historic_entry(t_buf *input, t_historic **history, int read)
{
	while ((*history)->next)
		(*history) = (*history)->next;
	ft_memdel((void **)&((*history)->origin));
	ft_memdel((void **)&((*history)->modif));
	reset_hist((*history)->prev);
	if (!input->s[0] || read || ((*history)->prev && !ft_strcmp(input->s, ((*history)->prev)->origin)))
		return ;
	if (!((*history)->origin = ft_strdup(input->s)) || !(((*history)->next) = ft_new_cmd_hist()))
		ft_exit(EXIT_FAILURE);
	((*history)->next)->prev = (*history);
	(*history) = (*history)->next;
}

void	enter_section(t_buf *input, t_list **lst, t_historic **history, int read)
{
	tputs(tgetstr("do", 0), 1, ft_writestdin);
	tputs(tgetstr("cr", 0), 1, ft_writestdin);
	historic_entry(input, history, read);
	// input start fct
	input->x = 0;
	ft_bzero(input->s, input->buf_size);
	caller_display(*lst, input);
	first_resize(-2);
}
