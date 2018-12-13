/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_input_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:47:38 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/12 18:45:23 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	*recall_prompt(t_alloc al, int type)
{
	static char		*input;
	char			*out;

	if (type == -1)
		return (input);
	else if (type == 1)
	{
		input = "heredoc";
		ft_memdel((void **)al.input->s);
		out = read_input(al);
		input = 0;
		return (out);
	}
	//addd if for all the types or recall
	return (0);
}

void	test(t_alloc al)
{
	char	*s;

	s = recall_prompt(al, 1);
	ft_printf("|%s|\n", al.input);
	ft_printf("|%s|\n", s);
}

char	*enter_section(t_alloc al, int read)
{
	size_t		x;

	x = (((display_sizing(0) + ft_strlen(al.input->s) - 1)
		/ window_width_size()) - (al.input->pos.l - 1)) + 1;
	while (--x)
		tputs(tgetstr("do", 0), 1, ft_writestdin);
	tputs(tgetstr("cr", 0), 1, ft_writestdin);
	ft_printf("%9s|%s|\n", "", al.input->s);
	if (read == -1)
		return (al.input->s);
	if (al.input->s[0] && !read)
	{
		set_terminal(0, 1);
		set_terminal(*al.env, 0);
		// test(al);
		// input start fct
		// input needed to be free and thats it
		// historic_entry(input, history, read, *lst);
		// a effectuer quand input done
	}
	al.input->x = 0;
	ft_bzero(al.input->s, al.input->buf_size);
	caller_display(*al.env, al.input, 1);
	return (0);
}
