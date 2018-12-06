/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/06 11:54:01 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void		analyzer(t_ast *sort, t_env *lst_env)
{
	static t_dispatch	dispatch[5];
	char				**tab_path;
	t_ast				*tmp;

	tmp = sort;
	tab_path = NULL;
	dispatch[0] = dispatch_cmd;
	dispatch[1] = dispatch_logic;
	dispatch[2] = dispatch_redir;
	dispatch[3] = dispatch_operator;
	dispatch[4] = dispatch_agreg;
	// while (tmp != NULL)
	// {
	// 	dispatch[tmp->type](tmp, lst_env, tab_path);
	// 	tmp = tmp->next;
	// }
	// (void)lst_env;
	if (tmp && tmp->print == 0)
	{
		ft_printf("Elem:\ntype = %d\ninput[0]: %s\n", tmp->type, tmp->input[0]);
		tmp->print = 1;
	}
	// while (tmp)
	// {
		if (tmp && tmp->left && tmp->left->print == 0)
			analyzer(tmp->left, lst_env);
		else if (tmp && tmp->right && tmp->right->print == 0)
			analyzer(tmp->right, lst_env);
		else if (tmp->back)
			analyzer(tmp->back, lst_env);
	// }
	// (tab_path) ? delete_str_tab(tab_path) : 0;
}
