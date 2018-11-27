/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/27 19:13:44 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void		analyzer(t_ast *lst, t_env *lst_env)
{
	static t_dispatch	dispatch[5];
	char				**tab_path;
	t_ast				*tmp;

	tmp = lst;
	tab_path = NULL;
	dispatch[0] = dispatch_cmd;
	dispatch[1] = dispatch_logic;
	dispatch[2] = dispatch_redir;
	dispatch[3] = dispatch_operator;
	dispatch[4] = dispatch_agreg;
	while (tmp != NULL)
	{
		dispatch[tmp->type](tmp, lst_env, tab_path);
		tmp = tmp->next;
	}
	(tab_path) ? delete_str_tab(tab_path) : 0;
}
