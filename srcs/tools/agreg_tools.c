/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agreg_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:20:09 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/14 14:55:44 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	agreg_type_1_2(int fd[3], t_ast *elem, t_alloc *alloc, int i)
{
	int	fd_new;

	fd_new = -1;
	fd_new = open(((elem->right) ? elem->right->input[0] :
		elem->input[1]), O_WRONLY | O_CREAT | ((i == 0)
		? O_TRUNC : O_APPEND), 0644);
	if (fd[1] != -1 && fd[2] != -1)
		close(fd_new);
		alloc->fd[1] = dup(1);
		alloc->fd[2] = dup(2);
	if (fd[1] == -1)
		fd[1] = fd_new;
	if (fd[2] == -1)
		fd[2] = fd_new;
}

static void	agreg_type_3(int fd[3], t_ast *elem, t_alloc *alloc)
{
	int	fd_tmp[3];
	int dig;
	int	fd_redir;
	int	fd_new;

	fd_tmp[0] = -1;
	fd_tmp[1] = -1;
	fd_tmp[2] = -1;
	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	fd_new = ft_atoi((dig == 1) ? elem->input[2] : elem->input[1]);
	if (fd_redir < 3 && fd_redir >= 0)
	{
		alloc->fd[fd_redir] = dup(fd_redir);
		fd[fd_redir] = fd_new;
		dup2(fd_redir, fd_new);
	}
	elem = elem->left;
	while (ft_is_redir(elem, fd_tmp, -1, -1, alloc) == 1)
		elem = elem->left;
	elem = elem->back;
	reinit_fd(fd_tmp, alloc);
	if (fd_tmp[fd_new] != -1)
		close(fd_redir);
}

static int	check_fd(t_ast *elem)
{
	int dig;
	int	fd_redir;
	int	fd_file;

	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	fd_file = ft_atoi((dig == 1) ? elem->input[2] : elem->input[1]);
	if (fd_redir == fd_file)
		return (1);
	if (dig == 0 && elem->input[1] && (fd_file
		= ft_fd_exist(elem->input[1])) == -1)
			return (-1);
	else if (dig == 1 && elem->input[2] && (fd_file
		= ft_fd_exist(elem->input[2])) == -1)
			return (-1);
	return (0);
}

int	ft_is_agreg(t_ast *elem, int fd[3], t_alloc *alloc)
{
	static char	*tab_agreg[5] = {"&>", "&>>", ">&", "<&-", ">&-"};
	int			i;
	int			ret;
	int			fd_redir;

	i = -1;
	fd_redir = -1;
	if (!elem)
		return (0);
	while (i++ < 4)
		if (ft_strcmp(elem->input[0], tab_agreg[i]) == 0
			|| ft_strcmp(elem->input[1], tab_agreg[i]) == 0)
		{
			((i == 0 || i == 1)) ? agreg_type_1_2(fd, elem, alloc, i) : 0;
			if (i == 2)
			{
				if ((ret = check_fd(elem)) != 0)
					return (ret);
				fd_redir = (ft_isdigit(elem->input[0][0]) == 1) ?
				ft_atoi(elem->input[0]) : 1;
				(fd[fd_redir] == -1) ? agreg_type_3(fd, elem, alloc) : 0;
			}
			return (1);
		}
	return (0);
}
