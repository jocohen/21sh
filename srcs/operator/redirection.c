/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:14:55 by tcollard          #+#    #+#             */
/*   Updated: 2019/03/05 18:26:09 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	redirection_1(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_redir(elem, fd, *alloc, lst_env) == 1 && elem->left)
		elem = elem->left;
	if (elem->back && elem->type != REDIR)
		elem = elem->back;
	if (elem->left)
		analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, *alloc);
}

void	redirection_2(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	(elem->right) ? elem->right->print = 1 : 0;
	while (ft_is_redir(elem, fd, *alloc, lst_env) == 1 && elem->left)
		elem = elem->left;
	if (elem->back && elem->type != REDIR)
		elem = elem->back;
	if (elem->left)
		analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, *alloc);
}

void	redirection_3(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int		fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	while (ft_is_redir(elem, fd, *alloc, lst_env) == 1 && elem->left)
		elem = elem->left;
	if (elem->back && elem->type != REDIR)
		elem = elem->back;
	if (elem->left)
		analyzer(elem->left, lst_env, alloc);
	reinit_fd(fd, *alloc);
}
