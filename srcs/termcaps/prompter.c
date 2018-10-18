/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:18:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/18 18:26:17 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

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
		ft_writestdin(k);
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
		caller_display(*lst);
	}
	else if (k == 27)
	{
		escape_analysis(input, 0, 0, history);
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
	caller_display(*lst);
	stdin_cpy = dup(0);
	while (1)
	{
		check_over_buffer(&input, 0);
		if (read(0, &k, 1) == -1)
		{
			if (g_pid == 1)
			{
				dup2(stdin_cpy, 0);
				enter_section(&input, lst, history, 1);
				k = -1;
				g_pid = 0;
			}
			else
				ft_exit(0);
		}
		check_prev_read(k);
		(k == 4 && !input.s[0]) ? tputs(tgetstr("do", 0), 1, ft_writestdin) : 0;
		if (k == 4 && !input.s[0])
		{
			lst_deletion(lst);
			ft_memdel((void **)&input.s);
			break ;
		}
		if (k != -1)
			analyse_input(&input, k, lst, history);
	}
}
