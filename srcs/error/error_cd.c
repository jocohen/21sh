/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:48:54 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/08 18:53:29 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	error_cd(char *err)
{
	write (2, "cd: no such file or directory: ", 31);
	write (2, err, ft_strlen(err));
	write (2, "\n", 1);
	return (-1);
}
