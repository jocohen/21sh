/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:04:43 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/12 16:32:08 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	sig_kill(int sig)
{
	(void)sig;
	if (g_pid == 666)
		kill(g_pid, SIGINT);
	g_pid = 1;
	close(0);
}

void	sig_window(int t)
{
	(void)t;
	g_resize = 1;
	close(0);
}
