/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eol_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:47:38 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/30 16:21:23 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	check_last_char_column(t_buf *input)
{
	if (input->pos.l && !input->pos.c)
	{
		tputs(tgetstr("im", 0), 1, ft_writestdin);
		write(1, "c", 1);
		input->pos.c += 1;
		cursor_movement(input, -2);
		tputs(tgetstr("dc", 0), 1, ft_writestdin);
		tputs(tgetstr("ei", 0), 1, ft_writestdin);
	}
}

void	reactualize_output(t_buf *input, t_list **lst)
{
	t_cursor	prev;

	prev.c = input->pos.c;
	prev.l = input->pos.l;
	check_last_char_column(input);
	delete_line_pos(input, lst);
	replace_cursor(input, prev.c, prev.l);
}

void	replace_cursor(t_buf *input, size_t c, size_t l)
{
	if (input->pos.l > l || (input->pos.l == l && input->pos.c > c))
	{
		while (input->pos.l != l || input->pos.c != c)
			cursor_movement(input, -2);
	}
	else if (input->pos.l < l || (input->pos.l == l && input->pos.c < c))
	{
		while (input->pos.l != l || input->pos.c != c)
			cursor_movement(input, 2);
	}
}

void	check_resize_curs_pos(t_buf *input)
{
	size_t		x;
	size_t		l;

	l = input->pos.c;
	x = display_sizing(0) + input->x;
	input->pos.l = x / window_width_size();
	input->pos.c = x % window_width_size();
	if ((l == (size_t)window_width_size() || (input->pos.l && l == 1)) && !input->pos.c && !input->s[input->x])
	{
		write(1, "c", 1);
		input->pos.c += 1;
		cursor_movement(input, -2);
		tputs(tgetstr("dc", 0), 1, ft_writestdin);
	}
}

void	vertical_cursor(t_buf *input, int direction)
{
	t_cursor	x;

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
	{
		x.c = (display_sizing(0) + ft_strlen(input->s)) % window_width_size();
		x.l = (display_sizing(0) + ft_strlen(input->s)) / window_width_size();
		if (input->pos.l == x.l)
			return ;
		input->x += window_width_size();
		if (x.l == input->pos.l + 1 && input->pos.c > x.c)
			input->x = ft_strlen(input->s);
		else
			x.c = input->pos.c;
		tputs(tgetstr("do",	0), 1, ft_writestdin);
		tputs(tgetstr("cr",	0), 1, ft_writestdin);
		input->pos.c = 0;
		input->pos.l += 1;
		while (input->pos.c != x.c)
		{
			tputs(tgetstr("nd", 0), 1, ft_writestdin);
			input->pos.c += 1;
		}
	}
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

void	historic_entry(t_buf *input, t_historic **history, int read, t_list *lst)
{
	int		fd;

	while ((*history)->next)
		(*history) = (*history)->next;
	ft_memdel((void **)&((*history)->origin));
	ft_memdel((void **)&((*history)->modif));
	reset_hist((*history)->prev);
	if (!input->s[0] || read || ((*history)->prev && !ft_strcmp(input->s, ((*history)->prev)->origin)))
		return ;
	fd = historic_opening(lst, 1);
	write(fd, input->s, ft_strlen(input->s));
	write(fd, "\n", 1);
	close(fd);
	if (!((*history)->origin = ft_strdup(input->s)) || !(((*history)->next) = ft_new_cmd_hist()))
		ft_exit(EXIT_FAILURE);
	((*history)->next)->prev = (*history);
	(*history) = (*history)->next;
}

char	*recall_prompt(t_list **lst, t_historic **history, int type)
{
	static char		*input;
	char			*out;

	if (type == -1)
		return (input);
	else if (type == 1)
	{
		input = "heredoc";
		out = prompt(lst, history);
		input = 0;
		return (out);
	}
	//addd if for all the types or recall
	return (0);
}

void	test(t_prompt shit)
{
	char	*s;

	s = recall_prompt(shit.lst, shit.hist, 1);
	ft_printf("|%s|\n", shit.input);
	ft_printf("|%s|\n", s);
}

char	*enter_section(t_buf *input, t_list **lst, t_historic **history, int read)
{
	size_t		x;
	t_prompt	main;

	x = (((display_sizing(0) + ft_strlen(input->s) - 1) / window_width_size()) - (input->pos.l - 1)) + 1;
	while (--x)
		tputs(tgetstr("do", 0), 1, ft_writestdin);
	tputs(tgetstr("cr", 0), 1, ft_writestdin);
	// ft_printf("%9s|%s|\n", "", input->s);
	if (read == -1)
		return (input->s);
	if (input->s[0] && !read)
	{
		main.input = input->s;
		main.lst = lst;
		main.hist = history;
		test(main);
		// input start fct
		// input needed to be free and thats it
		// historic_entry(input, history, read, *lst);
		// a effectuer quand input done
	}
	input->x = 0;
	ft_bzero(input->s, input->buf_size);
	caller_display(*lst, input, 1);
	return (0);
}
