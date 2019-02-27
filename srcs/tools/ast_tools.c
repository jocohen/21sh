/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:49:35 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/27 16:03:06 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void		link_new_node(t_ast **sort, t_ast *tmp, t_ast *node)
{
	t_ast	*h_node;

	h_node = node;
	if ((*sort)->type == LOGIC)
	{
		if (!node->right)
		{
			node->right = tmp;
			tmp->back = node;
		}
		else
		{
			tmp->left = node->right;
			node->right->back = tmp;
			node->right = tmp;
			tmp->back = node;
		}
	}
	else if (tmp->type != HEREDOC)
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
