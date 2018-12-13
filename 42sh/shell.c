/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:31:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/12 19:03:34 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		main(int ac, char **av, char **env)
{
	t_list		*lst;
	t_alloc		al;

	(void)ac;
	(void)av;
	g_clip = 0;
	g_pid = 0;
	g_resize = 0;
	lst = 0;
	if (!env_to_lst(env, &lst))
		ft_exit(0);
	al.env = &lst;
	prompt(al);
	lst_deletion(al.env);
	return (0);
}
