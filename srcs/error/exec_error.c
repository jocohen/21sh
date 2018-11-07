/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:10:58 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 12:16:54 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	exec_error(int err, char *files)
{
	(err == 0) ? write(2, "21sh: commnande not found: ", 27) : 0;
	if (err == 0)
		write(2, files, ft_strlen(files));
	write(2, "\n", 1);
	return (err);
}
