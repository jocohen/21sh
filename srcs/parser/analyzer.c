/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/13 14:00:50 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int		analyzer(t_ast *sort, t_env **lst_env, t_alloc **alloc)
{
	static t_dispatch	dispatch[] = { &dispatch_cmd, &dispatch_logic,
		&dispatch_redir, &dispatch_operator, &dispatch_agreg};
	char				**tab_path;
	t_ast				*tmp;
	int					ret;

	ret = 0;
	tmp = sort;
	tab_path = NULL;
	if (tmp && tmp->print == 0)
	{
		tmp->print = 1;
		return (dispatch[tmp->type](tmp, lst_env, tab_path, alloc));
	}
	if (tmp && tmp->left && tmp->left->print == 0)
		return (analyzer(tmp->left, lst_env, alloc));
	else if (tmp && tmp->right && tmp->right->print == 0)
		return (analyzer(tmp->right, lst_env, alloc));
	else if (tmp->back)
		return (analyzer(tmp->back, lst_env, alloc));
	return (ret);
}
