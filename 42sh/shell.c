/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:31:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/25 16:49:26 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		main(int ac, char **av, char **env)
{
	t_list		*lst;
	t_historic	*history;

	g_pid = 0;
	g_resize = 0;
	lst = 0;
	(void)ac;
	(void)av;
	if (!env_to_lst(env, &lst))
		ft_exit(0);
	init_hist(&history, lst);
	set_terminal(lst, 0);
	signal(SIGINT, sig_c);
	signal(SIGWINCH, sig_window);
	prompt(&lst, &history);
	lst_deletion(&lst);
	set_terminal(0, 1);
	return (0);
}
