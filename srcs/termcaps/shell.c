/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:31:12 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/13 14:45:24 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	reset_fd(void)
{
	int		stdout;

	if (!isatty(1))
	{
		ft_exit(0);
		stdout = dup(0);
		close(0);
		dup2(stdout, 0);
	}
	if (!isatty(0))
	{
		ft_exit(0);
		stdout = dup(1);
		close(1);
		dup2(stdout, 1);
	}
	if (!isatty(1))
		write(2, "21sh: bad files descriptor\n21sh: reset files descriptor\n",
			56);
}

int		main(int ac, char **av, char **env)
{
	t_env		*lst;
	t_alloc		al;

	(void)ac;
	(void)av;
	g_ret[0] = 0;
	g_ret[1] = 0;
	g_in_exec = 0;
	g_clip = 0;
	g_pid = 0;
	g_resize = 0;
	lst = 0;
	reset_fd();
	env_cp(env, &lst);
	al.env = &lst;
	prompt(&al);
	del_lst_env(al.env);
	return (0);
}
