/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:31:21 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/24 17:03:21 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
	&> 1 && 2 ecrir vers Z
	&>>
	>&

	<&-
	>&-
*/

void	agreg_1(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
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
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return ;
	(elem->right) ? elem->right->print = 1 : 0;
	save_err = dup(fd_err);
	save_out = dup(fd_out);
	dup2(fd_file, fd_out);
	dup2(fd_file, fd_err);
	analyzer(elem->left, lst_env, alloc);
	dup2(save_err, fd_err);
	dup2(save_out, fd_out);
}

void	agreg_2(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
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
		return ;
	(elem->right) ? elem->right->print = 1 : 0;
	save_err = dup(fd_err);
	save_out = dup(fd_out);
	dup2(fd_file, fd_out);
	dup2(fd_file, fd_err);
	analyzer(elem->left, lst_env, alloc);
	dup2(save_err, fd_err);
	dup2(save_out, fd_out);
}

void	agreg_3(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;
	int	dig;

	(void)tab_path;
	fd_file = 1;
	fd_redir = ((dig = ft_isdigit(elem->input[0][0]) == 1)) ?
		ft_atoi(elem->input[0]) : 1;
	if (elem->right &&(fd_file = open(elem->right->input[0], O_WRONLY |
		O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
	else if (dig == 0 && elem->input[1] && (fd_file = open(elem->input[1],
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
	else if (dig == 1 && elem->input[2] && (fd_file = open(elem->input[2],
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
	(elem->right) ? elem->right->print = 1 : 0;
	fd_save = dup(fd_redir);
	dup2(fd_file, fd_redir);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_redir);
}

void	agreg_4(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
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
}

void	agreg_5(t_ast *elem, t_env **lst_env, char **tab_path, t_alloc **alloc)
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
}
