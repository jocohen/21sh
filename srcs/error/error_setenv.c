/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:19:37 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/28 14:55:57 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	error_setenv(int i)
{
	if (i == 1)
		write(2, "21sh: setenv: usage: setenv [key] [value] [int overwrite]\n",
		58);
	else if (i == 2)
		write(2, "21sh: setenv: no '=' in the name\n", 33);
	else if (i == 3)
	{
		write(2, "21sh: setenv: too much arguments\n", 33);
		write(2, "usage: setenv [key] [value] [int overwrite]\n", 44);
	}
	return (-1);
}
