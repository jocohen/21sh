/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:33:39 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/08 19:10:40 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	error_unsetenv(int i, char *s)
{
	(i == 1) ? write(2, "21sh: unsetenv: too many arguments\n", 35) : 0;
	if (i == 2 || i == 1)
		write(2, "21sh: unsetenv: usage: unsetenv [key]\n", 38);
	else if (i == 3)
	{
		write(2, "21sh: unsetenv: ", 16);
		write(2, s, ft_strlen(s));
		write(2, " doesn't exist\n", 15);
	}
	g_ret = 256;
	return (-1);
}
