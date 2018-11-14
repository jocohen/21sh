/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/13 14:40:16 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void		analyzer(t_ast *lst, t_env *lst_env)
{
	static t_dispatch	dispatch[5];
	char				**tab_path;

	tab_path = NULL;
	dispatch[0] = dispatch_cmd;
	dispatch[1] = dispatch_logic;
	dispatch[2] = dispatch_redir;
	dispatch[3] = dispatch_operator;
	dispatch[4] = dispatch_agreg;
	convert_lst_tab(lst_env, &tab_path);
	while (lst != NULL)
	{
		dispatch[lst->type](lst, lst_env, tab_path);
		lst = lst->next;
	}
	delete_str_tab(tab_path);
	ft_printf("==> FINISH :-) <==\n\n");
}
