/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:14:55 by tcollard          #+#    #+#             */
/*   Updated: 2019/01/30 11:08:03 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	redirection_1(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;
	int	dig;

	fd_file = 1;
	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	if (elem->right && (fd_file = open(elem->right->input[0], O_WRONLY |
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

void	redirection_2(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;
	int	dig;

	fd_file = 1;
	dig = ft_isdigit(elem->input[0][0]);
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	if (elem->right && (fd_file = open(elem->right->input[0], O_WRONLY |
		O_CREAT | O_APPEND, 0644)) == -1)
		return ;
	else if (dig == 0 && elem->input[1] && (fd_file = open(elem->input[1],
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return ;
	else if (dig == 1 && elem->input[2] && (fd_file = open(elem->input[2],
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return ;
	(elem->right) ? elem->right->print = 1 : 0;
	fd_save = dup(fd_redir);
	dup2(fd_file, fd_redir);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_redir);
}

void	redirection_3(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;

	fd_redir = 0;
	if ((fd_file = open(elem->right->input[0], O_RDONLY)) == -1)
		return (error_redir(elem->right->input[0]));
	fd_save = dup(fd_redir);
	dup2(fd_file, fd_redir);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_redir);
}
