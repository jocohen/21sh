/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:25:49 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/28 18:22:40 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	selection_cmd(t_buf *input, char k, t_list **lst)
{
	if (k == 49 || k == 51)
	{
		ft_memdel((void **)&g_clip);
		if (!(g_clip = ft_strdup(selec_buffer(1, 0, 0)->s)))
			ft_exit(0);
		if (!g_clip[0])
			ft_memdel((void **)&g_clip);
	}
	else if (k == 50)
		paste_intra_clip(input, lst);
	if (k == 51)
		cut_selection(input, selec_buffer(1, 0, 0), lst);
}

void	selection_input(t_buf *input, char k, t_list **lst)
{
	if (k == 68)
		selection_init(input, -1, lst);
	else if (k == 67)
		selection_init(input, 1, lst);
}

void	ctrl_arrow_move(t_buf *input, char k)
{
	if (k == 68)
		while (input->x)
		{
			cursor_movement(input, -1);
			if (input->x && !(ft_isalnum(input->s[input->x - 1])) && ft_isalnum(input->s[input->x]))
				break ;
		}
	else if (k == 67)
		while (input->s[input->x])
		{
			cursor_movement(input, 1);
			if (input->s[input->x] && !(ft_isalnum(input->s[input->x - 1])) && ft_isalnum(input->s[input->x]))
				break ;
		}
	else if (k == 65)
		vertical_cursor(input, -1);
	else if (k == 66)
		vertical_cursor(input, 1);
}

void	del_char(t_buf *input, int type, t_list **lst)
{
	if (!type)
	{
		if (!input->x)
			return ;
		cursor_movement(input, -1);
		tputs(tgetstr("dc", 0), 1, ft_writestdin);
		ft_memmove(input->s + input->x, input->s + input->x + 1,
			ft_strlen(input->s + input->x + 1) + 1);
		reactualize_output(input, lst);
	}
	else if (input->s[input->x])
	{
		ft_memmove(input->s + input->x, input->s + input->x + 1,
			ft_strlen(input->s + input->x + 1) + 1);
		tputs(tgetstr("dc", 0), 1, ft_writestdin);
		reactualize_output(input, lst);
	}
}

void	home_end_move(t_buf *input, char k)
{
	if (k == 72)
		while (input->x)
			cursor_movement(input, -1);
	else if (k == 70)
		while (input->s[input->x])
			cursor_movement(input, 1);
}

void	arrow_move(t_buf *input, char k, t_historic **history, t_list **lst)
{
	if (k == 68 && input->x)
		cursor_movement(input, -1);
	else if (k == 67 && input->s[input->x])
		cursor_movement(input, 1);
	else if (k == 65)
		historic_move(input, history, -1, lst);
	else if (k == 66)
		historic_move(input, history, 1, lst);
}

void	page_move(t_buf *input, char k, t_historic **history, t_list **lst)
{
	if (k == 53)
		historic_move(input, history, -1, lst);
	else if (k == 54)
		historic_move(input, history, 1, lst);
}

void	escape_analysis(t_buf *input, t_historic **history, t_list **lst)
{
	static char	key[6];
	char		c;
	size_t		y;

	c = 0;
	y = 0;
	ft_bzero(key, 6);
	while (y < 5)
	{
		if ((read(0, &c, 1)) == -1)
			ft_exit(0);
		key[y++] = c;
		if ((key[1] && key[1] != 49 && key[1] != 50 && key[1] != 51) || (key[3] && key[3] != 50))
			selec_buffer(0, input, lst);
		if (key[0] == 91 && key[1] >= 65 && key[1] <= 68)
			return (arrow_move(input, key[1], history, lst));
		else if (key[0] == 91 && (key[1] == 72 || key[1] == 70))
			return (home_end_move(input, key[1]));
		else if (key[0] == 91 && key[1] == 51 && key[2] == 126)
			return (del_char(input, 1, lst));
		else if (key[0] == 91 && key[1] == 49 && key[2] == 59 && key[3] == 53
			&& key[4] >= 65 && key[4] <= 68)
			return (ctrl_arrow_move(input, key[4]));
		else if (key[0] == 91 && key[1] == 49 && key[2] == 59 && key[3] == 50
			&& key[4] >= 67 && key[4] <= 68)
			return (selection_input(input, key[4], lst));
		else if (key[0] == 91 && key[2] == 126 && key[1] >= 53 && key[1] <= 54)
			return (page_move(input, key[1], history, lst));
		else if (key[0] == 116 && key[1] >= 49 && key[1] <= 51)
			return (selection_cmd(input, key[1], lst));
		else if ((key[0] != 91 && key[0] != 116) || (key[1] < 65 && key[1] > 68 && key[1] != 72 &&
			key[1] != 70 && key[1] != 49 && key[1] != 51 && key[1] != 53 && key[1] != 54 &&
			key[1]) || (key[2] != 59 && key[2]) || (key[3] != 53 && key[3] != 50 && key[3])
			|| (key[4] < 65 && key[4] > 67 && key[4]))
			return ;
	}
}
