/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:49:35 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/27 12:21:26 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void		link_new_node(t_ast **sort, t_ast *tmp, t_ast *node)
{
	t_ast	*h_node;

	h_node = node;
	if (tmp->type != CMD && tmp->type != HEREDOC)
	{
		tmp->left = node;
		node->back = tmp;
		if ((*sort)->type != LOGIC)
			*sort = tmp;
	}
	else
	{
		tmp->left = *sort;
		(*sort)->back = tmp;
		*sort = tmp;
	}
}
