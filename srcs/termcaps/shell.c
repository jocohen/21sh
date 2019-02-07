/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:31:12 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/07 18:13:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		main(int ac, char **av, char **env)
{
	t_env		*lst;
	t_alloc		al;
	int			stdout;

	(void)ac;
	(void)av;
	if (!isatty(1) || !isatty(0))
		write(2, "21sh: bad files descriptor\n21sh: reset files descriptor\n", 56);
	stdout = dup(0);
	close(0);
	dup2(stdout, 0);
	stdout = dup(1);
	close(1);
	dup2(stdout, 1);
	g_ret = 0;
	g_in_exec = 0;
	g_clip = 0;
	g_pid = 0;
	g_resize = 0;
	lst = 0;
	if (!env_cp(env, &lst))
		ft_exit(0);
	al.env = &lst;
	prompt(&al);
	del_lst_env(al.env);
	return (0);
}
