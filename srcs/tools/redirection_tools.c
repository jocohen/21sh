/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:32:04 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/12 00:40:34 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_is_redir1(t_ast *elem, int fd[3], int fd_redir, int fd_open,
		t_alloc *alloc)
{
	static char		*tab_redir[7] = {">", ">>", ">>&", "<", "<<<", "<>", "<<"};
	int				i;
	int				dig;

	i = -1;
	dig = 0;
	if (!elem)
		return (0);
	while (i++ < 6)
		if (ft_strcmp(elem->input[0], tab_redir[i]) == 0
			|| ft_strcmp(elem->input[1], tab_redir[i]) == 0)
		{
			dig = ft_isdigit(elem->input[0][0]);
			fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
			fd_open = open(elem->right->input[0], O_WRONLY | O_CREAT
				| ((i == 0) ? O_TRUNC : O_APPEND), 0644);
			if (fd_redir < 3 && fd_redir >= 0 && fd[fd_redir] == -1)
			{
				fd[fd_redir] = fd_open;
				alloc->fd[fd_redir] = dup(fd_redir);
				dup2(fd_open, fd_redir);
			}
			else
				close(fd_open);
			return (1);
		}
	return (0);
}

void	reinit_fd(int fd[3], t_alloc *alloc)
{
	ft_printf("fd[1]: %d    fd[2]: %d\n", alloc->fd[1], alloc->fd[2]);
	if (fd[1] != -1)
	{
		dup2(alloc->fd[1], 1);
		close(fd[1]);
	}
	if (fd[2] != -1)
	{
		dup2(alloc->fd[2], 2);
		close(fd[2]);
	}
}
