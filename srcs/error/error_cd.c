/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:48:54 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/19 16:40:16 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	error_cd(char *err, int type)
{
	if (type == 0)
		write(2, "cd: no such file or directory: ", 31);
	else if (type == 1)
		write(2, "cd: permission denied: ", 23);
	else if (type == 2)
		write(2, "cd: ", 4);
	write(2, err, ft_strlen(err));
	(type == 2) ? write(2, " not set", 8) : 0;
	write(2, "\n", 1);
	return (-1);
}
