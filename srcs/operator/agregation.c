/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:31:21 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/12 11:48:28 by tcollard         ###   ########.fr       */
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
			if (i == 0 || i == 1)
			{
				fd_new = open(elem->right->input[0], O_WRONLY | O_CREAT
				| ((i == 0) ? O_TRUNC : O_APPEND), 0644);
				if (fd[1] != -1 && fd[2] != -1)
					close(fd_new);
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
					ft_printf("ICI\n");
					ft_printf("fd_redir: %d\nfd_new: %d\n", fd_redir, fd_new);
					fd[fd_redir] = fd_new;
					ft_printf("fd[1]: %d    fd[2]: %d\n", alloc->fd[1], alloc->fd[2]);
					alloc->fd[fd_redir] = dup(fd_new);
					dup2(fd_redir, fd_new);
					close(fd_redir);
				}
			}
			return (1);
		}
	}
	// if (fd_file == -1 && ft_is_redir(elem, fd, 1, -1) == 1)
	// 	return (1);
	return (0);
}

int	agreg_1(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	save_out;
	int save_err;
	int fd[3];

	(void)tab_path;
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd_file = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_agreg(elem, fd, fd_file, *alloc) == 1)
		elem = elem->left;
	elem = elem->back;
	save_err = dup(2);
	save_out = dup(1);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	dup2(save_err, 2);
	dup2(save_out, 1);
	close(fd_file);
	return (0);
}

int	agreg_2(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	save_out;
	int save_err;
	int fd[3];

	(void)tab_path;
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd_file = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_agreg(elem, fd, fd_file, *alloc) == 1)
		elem = elem->left;
	elem = elem->back;
	save_err = dup(2);
	save_out = dup(1);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	dup2(save_err, 2);
	dup2(save_out, 1);
	close(fd_file);
	return (0);
}

int	agreg_3(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	fd_redir;
	int	dig;
	// int	save_out;
	// int save_err;
	int fd[3];

	(void)tab_path;
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd_file = -1;



	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;

	(elem->right) ? elem->right->print = 1 : 0;

	if (dig == 0 && elem->input[1] && (fd_file =
		ft_fd_exist(elem->input[1])) == -1)
		return (-1);
	else if (dig == 1 && elem->input[2] && (fd_file =
		ft_fd_exist(elem->input[2])) == -1)
		return (-1);


	while (ft_is_agreg(elem, fd, -1, *alloc) == 1
	|| ft_is_redir(elem, fd, -1, -1, *alloc) == 1)
		elem = elem->left;
	elem = elem->back;
	// save_err = dup(2);
	// save_out = dup(1);
	// dup2(fd[1], 1);
	// dup2(fd[2], 2);
	ft_printf("fd1 = %d  fd2 = %d\n", fd[1], fd[2]);
	ft_printf("fd[1]: %d	fd[2]: %d\n", (*alloc)->fd[1], (*alloc)->fd[2]);
	analyzer(elem->left, lst_env, alloc);

	reinit_fd(fd, *alloc);

	// if (fd[1] != -1)
	// 	close(fd[1]);
	// if (fd[2] != -1)
	// 	close(fd[2]);
	// fd[1] = 1;
	// fd[2] = 2;
	// dup2(fd[1] , 1);
	// dup2(fd[2] , 2);
	// dup2(fd_file, fd_redir);
	// close(fd_file);
	// dup2(save_err, 2);
	// dup2(save_out, 1);

	// fd[fd_redir] = fd_redir;
	return (0);














	// int	fd_file;
	// int	fd_save;
	// int	fd_redir;
	// int	dig;
	//
	// (void)tab_path;
	// fd_file = 1;
	// dig = ft_isdigit(elem->input[0][0]);
	// fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	//
	//
	// // if (elem->right && (fd_file = ft_fd_exist(elem->right->input[0])) == -1)
	// // 	return (-1);
	// if (dig == 0 && elem->input[1] && (fd_file =
	// 	ft_fd_exist(elem->input[1])) == -1)
	// 	return (-1);
	// else if (dig == 1 && elem->input[2] && (fd_file =
	// 	ft_fd_exist(elem->input[2])) == -1)
	// 	return (-1);
	// (elem->right) ? elem->right->print = 1 : 0;
	// // ft_printf("in[0]: %s\nin[1]: %s\nin[2]: %s\n", elem->input[0], elem->input[1], elem->input[2]);
	// // ft_printf("redir: %d\nfile: %d\n", fd_redir, fd_file);
	// fd_save = dup(fd_redir);
	// dup2(fd_file, fd_redir);
	// analyzer(elem->left, lst_env, alloc);
	// dup2(fd_save, fd_redir);
	// close(fd_save);
	// (fd_redir > 3) ? close(fd_redir) : 0;
	// return (0);
	//
	//
	// int	fd_file;
	// int	fd_save;
	// int	fd_redir;
	// int	dig;
	//
	// (void)tab_path;
	// fd_file = 1;
	// ft_printf("ELEM IN[0]: |%s|\n", elem->input[0]);
	// ft_printf("ELEM IN[1]: |%s|\n", elem->input[1]);
	// ft_printf("ELEM IN[2]: |%s|\n", elem->input[2]);
	// dig = ft_isdigit(elem->input[0][0]);
	// fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	// if (elem->right == NULL)
	// 	ft_printf("NULL\n");
	// else
	// {
	// 	ft_printf("OK\n");
	// 	ft_printf("elem: %s\n", elem->right->input[0]);
	// }
	// if (elem->right && (fd_file = ft_fd_exist(elem->right->input[0])) == -1)
	// 	return (-1);
	// else if (dig == 0 && elem->input[1] && (fd_file =
	// 	ft_fd_exist(elem->input[1])) == -1)
	// 	return (-1);
	// else if (dig == 1 && elem->input[2] && (fd_file =
	// 	ft_fd_exist(elem->input[2])) == -1)
	// 	return (-1);
	// (elem->right) ? elem->right->print = 1 : 0;
	// fd_save = dup(fd_redir);
	// dup2(fd_file, fd_redir);
	// analyzer(elem->left, lst_env, alloc);
	// dup2(fd_save, fd_redir);
	// close(fd_save);
	// (fd_redir > 3) ? close(fd_redir) : 0;
	// return (0);
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
