/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:31:21 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/11 17:09:45 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_is_agreg(t_ast *elem, int fd[3], int fd_file)
{
	static char	*tab_agreg[5] = {"&>", "&>>", ">&", "<&-", ">&-"};
	int			i;
	int			fd_new;

	i = -1;
	fd_new = -1;
	if (!elem)
		return (0);
	while (i++ < 4)
	{
		if (ft_strcmp(elem->input[0], tab_agreg[i]) == 0
			|| ft_strcmp(elem->input[1], tab_agreg[i]) == 0)
		{
			fd_new = open(elem->right->input[0], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
			if (fd[1] != -1 && fd[2] != -1)
				close(fd_new);
			if (fd[1] == -1)
				fd[1] = fd_new;
			if (fd[2] == -1)
				fd[2] = fd_new;
			return (1);
		}
	}
	if (fd_file == -1 && ft_is_redir1(elem, fd, 1, -1) == 1)
		return (1);
	return (0);
}

int	agreg_1(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	save_out;
	int save_err;
	int	fd_out;
	int	fd_err;

	int fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;

	(void)tab_path;
	fd_out = 1;
	fd_err = 2;
	fd_file = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_agreg(elem, fd, fd_file) == 1)
		elem = elem->left;
	elem = elem->back;
	save_err = dup(2);
	save_out = dup(1);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	dup2(save_err, fd_err);
	dup2(save_out, fd_out);
	close(fd_file);
	return (0);
}

int	agreg_2(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	save_out;
	int save_err;
	int	fd_out;
	int	fd_err;

	(void)tab_path;
	fd_out = 1;
	fd_err = 2;
	fd_file = 0;
	if (elem->right && (fd_file = open(elem->right->input[0],
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return (-1);
	(elem->right) ? elem->right->print = 1 : 0;
	save_err = dup(fd_err);
	save_out = dup(fd_out);
	dup2(fd_file, fd_out);
	dup2(fd_file, fd_err);
	analyzer(elem->left, lst_env, alloc);
	dup2(save_err, fd_err);
	dup2(save_out, fd_out);
	return (0);
}

int	agreg_3(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;
	int	dig;

	(void)tab_path;
	fd_file = 1;
	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;


	// if (elem->right && (fd_file = ft_fd_exist(elem->right->input[0])) == -1)
	// 	return (-1);
	if (dig == 0 && elem->input[1] && (fd_file =
		ft_fd_exist(elem->input[1])) == -1)
		return (-1);
	else if (dig == 1 && elem->input[2] && (fd_file =
		ft_fd_exist(elem->input[2])) == -1)
		return (-1);
	(elem->right) ? elem->right->print = 1 : 0;
	ft_printf("in[0]: %s\nin[1]: %s\nin[2]: %s\n", elem->input[0], elem->input[1], elem->input[2]);
	ft_printf("redir: %d\nfile: %d\n", fd_redir, fd_file);
	fd_save = dup(fd_redir);
	dup2(fd_file, fd_redir);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_redir);
	close(fd_save);
	(fd_redir > 3) ? close(fd_redir) : 0;
	return (0);


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
