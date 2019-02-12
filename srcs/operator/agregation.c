/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:31:21 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/12 18:01:21 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_is_agreg(t_ast *elem, int fd[3], int fd_file, t_alloc *alloc)
{
	static char	*tab_agreg[5] = {"&>", "&>>", ">&", "<&-", ">&-"};
	int			i;
	int			fd_new;
	int			dig;
	int			fd_redir;

	(void)fd_file;
	i = -1;
	fd_new = -1;
	fd_redir = -1;
	dig = ft_isdigit(elem->input[0][0]);
	if (!elem)
		return (0);
	while (i++ < 4)
	{
		if (ft_strcmp(elem->input[0], tab_agreg[i]) == 0
			|| ft_strcmp(elem->input[1], tab_agreg[i]) == 0)
		{
			if ((i == 0 || i == 1))
			{
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
			else if (i == 2)
			{
				fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
				if (dig == 0 && elem->input[1] && (fd_new =
					ft_fd_exist(elem->input[1])) == -1)
					return (-1);
				else if (dig == 1 && elem->input[2] && (fd_new =
					ft_fd_exist(elem->input[2])) == -1)
					return (-1);
				if (fd[fd_redir] == -1)
				{
					fd[fd_redir] = fd_new;
					alloc->fd[1] = dup(1);
					alloc->fd[2] = dup(2);
					ft_printf("%d vers %d\n", fd_redir, fd_new);
					dup2(fd_redir, fd_new);
					// if (elem->left && elem->left->type != CMD)
					// {
					// 	ft_printf("close fd %d\n", fd_redir);
					// 	close(fd_redir);
					// }
				}
			}
			return (1);
		}
	}
	return (0);
}

int	agreg_1(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int fd[3];
	int	ret1;
	int	ret2;

	(void)tab_path;
	ret1 = -1;
	ret2 = -1;
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd_file = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while ((ret1 = ft_is_agreg(elem, fd, fd_file, *alloc)) == 1
		|| (ret2 = ft_is_redir(elem, fd, -1, -1, *alloc)) == 1)
		elem = elem->left;
	elem = elem->back;
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, *alloc);
	return (0);
}

int	agreg_2(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int fd[3];

	(void)tab_path;
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd_file = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_agreg(elem, fd, fd_file, *alloc) == 1
		|| ft_is_redir(elem, fd, -1, -1, *alloc) == 1)
		elem = elem->left;
	elem = elem->back;
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, *alloc);
	return (0);
}

int	agreg_3(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	fd_redir;
	int	ret1;
	int	ret2;
	int	dig;
	int	fd[3];
	int	i;

	(void)tab_path;
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd_file = -1;
	fd_redir = -1;
	ret1 = 0;
	ret2 = 0;
	i = 1;

	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	(elem->right) ? elem->right->print = 1 : 0;
	while ((ret1 = ft_is_agreg(elem, fd, fd_file, *alloc)) == 1
		|| (ret2 = ft_is_redir(elem, fd, -1, -1, *alloc)) == 1)
		elem = elem->left;
	elem = elem->back;
	if (ret1 == -1 || ret2 == -1)
		return (-1);

	// i = 1;
	// while (i < 3)
	// {
	// 	ft_printf("fd[%d] = %d\n", i, fd[i]);
	// 	if (fd[i] != -1)
	// 		close(i);
	// 	i += 1;
	// }

	analyzer(elem->left, lst_env, alloc);
	dup2((*alloc)->fd[1], 1);
	dup2((*alloc)->fd[2], 2);
	return(0);
}

int	agreg_4(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_close;
	int	fd_save;

	(void)tab_path;
	fd_close = (ft_isdigit(elem->input[0][0]) == 1) ?
		ft_atoi(elem->input[0]) : 0;
	fd_save = dup(fd_close);
	close(fd_close);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_close);
	return (0);
}

int	agreg_5(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_close;
	int	fd_save;

	(void)tab_path;
	fd_close = (ft_isdigit(elem->input[0][0]) == 1) ?
		ft_atoi(elem->input[0]) : 1;
	fd_save = dup(fd_close);
	close(fd_close);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_close);
	return (0);
}
