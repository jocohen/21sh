/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:10:58 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/12 15:31:26 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	exec_error(int err, char *files, t_alloc **alloc)
{
	(err == -1) ? write(2, "21sh: commande not found: ", 26) : 0;
	if (err == -1)
		write(2, files, ft_strlen(files));
	write(2, "\n", 1);
	del_alloc(alloc);
	return (err);
}
