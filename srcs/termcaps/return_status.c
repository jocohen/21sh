/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:44:12 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/08 19:08:38 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ret_status()
{
	int		err;

	err = 0;
	if (WIFEXITED(g_ret))
		err = WEXITSTATUS(g_ret);
	else if (WIFSIGNALED(g_ret))
		err = WTERMSIG(g_ret);
	else if (WIFSTOPPED(g_ret))
		err = WSTOPSIG(g_ret);
	return (err);
}
