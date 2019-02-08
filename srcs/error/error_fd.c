/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:53:50 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/08 14:42:25 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_fd_exist(char *str_fd)
{
	int			fd;
	int			ret;

	if (!str_fd)
		return (0);
	fd = ft_atoi(str_fd);
	ret = dup(fd);
	if (ret == -1)
	{
		write(2, "21sh: ", 6);
		write(2, str_fd, ft_strlen(str_fd));
		write(2, ": bad file descriptor\n", 22);
		return (-1);
	}
	close(ret);
	return (fd);
}
