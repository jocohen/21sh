/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:10:58 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/15 13:05:45 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	exec_error(int err, char *files)
{
	(err == -1) ? write(2, "21sh: commande not found: ", 26) : 0;
	if (err == -1)
		write(2, files, ft_strlen(files));
	write(2, "\n", 1);
	return (127);
}

int	exec_right_error(int err, char *files)
{
	if (err == 1)
	{
		write(2, "21sh: ", 6);
		write(2, files, ft_strlen(files));
		write(2, ": no such file or directory\n", 28);
		g_ret[0] = 127;
	}
	else if (err == 2)
	{
		write(2, "21sh: ", 6);
		write(2, files, ft_strlen(files));
		write(2, ": permission denied\n", 20);
		g_ret[0] = 126;
	}
	return (1);
}
