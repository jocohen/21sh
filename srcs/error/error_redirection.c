/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 23:59:15 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/22 00:01:10 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	error_redir(char *file)
{
	write(2, "21sh: no such file or directory: ", 33);
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
}
