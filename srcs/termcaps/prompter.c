/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:18:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/14 16:04:13 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	*kill_or_give(t_alloc *al, char k)
{
	(k != 27 && k != -1) ? selec_buffer(0, al->input, al->env) : 0;
	if (k == 4 && !al->input->s[0] && !recall_prompt(al, -1))
	{
		tputs(tgetstr("do", 0), 1, ft_writestdin);
		tputs(tgetstr("cr", 0), 1, ft_writestdin);
		ft_memdel((void **)&(al->input->s));
		return (0);
	}
	if (k == 10)
	{
		if (recall_prompt(al, -1))
			return (enter_section(al, -1));
		if (ft_strncmp("exit", al->input->s, 4) == 0 && !recall_prompt(al, -1))
		{
			// del_alloc(&al);
			ft_memdel((void *)&(al->input->s));
			return (0);
		}
		enter_section(al, 0);
	}
	return (al->input->s);
}

char	*read_and_sig(t_alloc *al, char *k, int stdin_cpy)
{
	check_over_buffer(al->input, 0);
	if (read(0, k, 1) == -1)
	{
		if (!g_pid && !g_resize)
			ft_exit(0);
		*k = -1;
		dup2(stdin_cpy, 0);
		if (g_pid == -1 && recall_prompt(al, -1))
		{
			ft_memdel((void **)&(al->input->s));
			return (enter_section(al, -1));
		}
		(g_pid == -1) ? enter_section(al, 1) : 0;
		(g_resize == 1) ? check_resize_curs_pos(al->input) : 0;
		g_pid = 0;
		g_resize = 0;
	}
	check_prev_read(*k);
	return (k);
}

char	*read_input(t_alloc *al)
{
	char		k;
	t_buf		input;
	int			stdin_cpy;

	al->input = &input;
	al->input->buf_size = 128;
	if (!(al->input->s = ft_memalloc(al->input->buf_size)))
		ft_exit(0);
	al->input->x = 0;
	caller_display(*al->env, al->input, 1);
	stdin_cpy = dup(0);
	while (1)
	{
		if (!read_and_sig(al, &k, stdin_cpy))
			return (0);
		if (!kill_or_give(al, k))
			break ;
		else if (k == 10 && recall_prompt(al, -1))
			return (al->input->s);
		if (k != 10)
			analyse_input(al, k);
	}
	return (0);
}

void	prompt(t_alloc *al)
{
	t_historic	*history;

	init_hist(&history, *al->env);
	al->history = &history;
	set_terminal(*al->env, 0);
	signal(SIGINT, sig_kill);
	signal(SIGWINCH, sig_window);
	read_input(al);
	ft_del_hist(&history);
	set_terminal(0, 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}
