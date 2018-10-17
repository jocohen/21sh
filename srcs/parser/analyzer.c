/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/16 19:21:38 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
**	TO DO:
**	 	1 - clean quote:
**	 		- cp str and remove quote
**	 		- if quote = '"' check for var env '$' and replace
**	 	2 - fill structure:
**	 	 	- check if first char is operator (cmd = operator / option = <>|)
*/

void		analyzer(t_ast *lst)
{
	t_dispatch	dispatch[5];

	dispatch[0] = dispatch_cmd;
	dispatch[1] = dispatch_logic;
	dispatch[2] = dispatch_redir;
	dispatch[3] = dispatch_operator;
	dispatch[4] = dispatch_aggreg;
	while (lst != NULL)
	{
		dispatch[lst->type](lst);
		lst = lst->next;
	}
	ft_printf("FINISH :-)\n");
}
