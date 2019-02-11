/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/11 14:29:18 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		analyzer(t_ast *sort, t_env **lst_env, t_alloc **alloc)
{
	static t_dispatch	dispatch[] = { &dispatch_cmd, &dispatch_logic,
		&dispatch_redir, &dispatch_operator, &dispatch_agreg};
	char				**tab_path;
	t_ast				*tmp;
	int					ret;

	int i;
	i = 0;


	ret = 0;
	tmp = sort;
	tab_path = NULL;
	if (tmp && tmp->print == 0)
	{
		// i = 0;
		// while (tmp->input[i])
		// {
		// 	ft_printf("input[%d]: |%s|\n", i, tmp->input[i]);
		// 	i += 1;
		// }
		// ft_printf("ELEM TO DISPATCH: |%s|\n", tmp->input[0]);
		//
		// ft_printf("ELEM TO DISPATCH: |%s|\n", tmp->input[1]);
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
