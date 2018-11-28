/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:33:39 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/28 15:37:16 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inludes/ft_21sh.h"

int	error_setenv(int i, char *s)
{
	if (i == 1)
		write(2, "21sh: unsetenv: usage: unsetenv [key]\n", 38);
	else if (i == 2)
	{
		write(2, "21sh: unsetenv: ", 16);
		write(2, s, ft_strlen(s));
		write(2, " doesn't exist\n", 15);
	}
	return (-1);
}
