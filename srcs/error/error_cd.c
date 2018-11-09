/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:48:54 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/09 11:47:38 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	error_cd(char *err, int type)
{
	if (type == 0)
		write(2, "cd: no such file or directory: ", 31);
	else if (type == 1)
		write(2, "cd: permission denied: ", 23);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (-1);
}
