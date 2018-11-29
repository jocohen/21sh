/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:33:39 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/29 10:22:50 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

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
	return (-1);
}
