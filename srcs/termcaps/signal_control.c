/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:04:43 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/19 12:33:08 by nicolaslamerenx  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	sig_kill(int sig)
{
	(void)sig;
	if (g_in_exec)
	{
		g_in_exec = 0;
		kill(g_pid, SIGINT);
	}
	if (!g_pid)
		close(0);
	g_pid = -1;
}

void	sig_window(int t)
{
	(void)t;
	g_resize = 1;
	close(0);
}
