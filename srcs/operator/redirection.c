/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:14:55 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/07 18:45:33 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	redirection_1(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_save1;
	int	fd_save2;
	int	fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_redir1(elem, fd, -1, -1) == 1)
		elem = elem->left;
	elem = elem->back;
	fd_save1 = dup(1);
	fd_save2 = dup(2);
	if (fd[1] != -1)
		dup2(fd[1], 1);
	if (fd[2] != -1)
		dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, fd_save1, fd_save2);
}

void	redirection_2(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_save1;
	int	fd_save2;
	int	fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_redir1(elem, fd, -1, -1) == 1)
		elem = elem->left;
	elem = elem->back;
	fd_save1 = dup(1);
	fd_save2 = dup(2);
	if (fd[1] != -1)
		dup2(fd[1], 1);
	if (fd[2] != -1)
		dup2(fd[2], 2);
	analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, fd_save1, fd_save2);
}

void	redirection_3(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;

	fd_redir = 0;
	if ((fd_file = open(elem->right->input[0], O_RDONLY)) == -1)
	{
		if (access(elem->right->input[0], F_OK) == -1)
			return (error_access(elem->right->input[0]));
		else
			return (error_redir(elem->right->input[0]));
	}
	fd_save = dup(fd_redir);
	dup2(fd_file, fd_redir);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_redir);
}
