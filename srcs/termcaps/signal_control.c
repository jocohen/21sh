/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:04:43 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/01 14:15:04 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	sig_c(int sig)
{
	(void)sig;
	if (g_pid == 666)
		kill(g_pid, SIGINT);
	g_pid = 1;
	close(0);
}
