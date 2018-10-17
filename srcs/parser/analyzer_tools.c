/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:17:43 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/16 19:47:31 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	dispatch_cmd(t_ast *elem)
{
	ft_printf("CMD:\n->type: %d\n->value: %s\n->opt: %s\n->content: %s\n\n",
	elem->type, elem->value, elem->opt, elem->content);
	builtins_dispatch(elem);
}

void	dispatch_logic(t_ast *elem)
{
	ft_printf("LOGIC:\n->type: %d\n->value: %s\n->opt: %s\n->content: %s\n\n",
	elem->type, elem->value, elem->opt, elem->content);
}

void	dispatch_redir(t_ast *elem)
{
	ft_printf("REDIR:\n->type: %d\n->value: %s\n->opt: %s\n->content: %s\n\n",
	elem->type, elem->value, elem->opt, elem->content);
}

void	dispatch_operator(t_ast *elem)
{
	ft_printf("OPER:\n->type: %d\n->value: %s\n->opt: %s\n->content: %s\n\n",
	elem->type, elem->value, elem->opt, elem->content);
}

void	dispatch_aggreg(t_ast *elem)
{
	ft_printf("AGGREG:\n->type: %d\n->value: %s\n->opt: %s\n->content: %s\n\n",
	elem->type, elem->value, elem->opt, elem->content);
}
