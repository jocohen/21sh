/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:31:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/05 14:59:14 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int		main(int ac, char **av, char **env)
{
	t_list	*lst;
	t_historic	*history;

	g_pid = 0;
	lst = 0;
	(void)ac;
	(void)av;
	if (!env_to_lst(env, &lst))
		ft_exit(0);
	init_hist(&history, lst);
	set_terminal(lst, 0);
	signal(SIGINT, sig_c);
	prompt(&lst, &history);
	lst_deletion(&lst);
	set_terminal(0, 1);
	return (0);
}
