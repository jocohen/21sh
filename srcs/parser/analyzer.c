/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/08 17:13:50 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void		analyzer(t_ast *lst, t_env *lst_env, char **tab_env)
{
	static t_dispatch	dispatch[5];

	dispatch[0] = dispatch_cmd;
	dispatch[1] = dispatch_logic;
	dispatch[2] = dispatch_redir;
	dispatch[3] = dispatch_operator;
	dispatch[4] = dispatch_agreg;
	while (lst != NULL)
	{
		dispatch[lst->type](lst, lst_env, tab_env);
		lst = lst->next;
	}
	ft_printf("==> FINISH :-) <==\n\n");
}
