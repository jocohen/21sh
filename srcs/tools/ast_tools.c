/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:49:35 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/26 10:52:33 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// static void	insert_between(t_ast *node, t_ast *tmp)
// {
// 	tmp->left = node;
// 	tmp->back = node->back;
// 	node->back->right = tmp;
// 	node->back = tmp;
// }
//
// static void	insert_end(t_ast *node, t_ast *tmp)
// {
// 	tmp->left = node->right;
// 	node->right->back = tmp;
// 	tmp->back = node;
// 	node->right = tmp;
// }

void		link_new_node(t_ast **sort, t_ast *tmp, t_ast *node)
{

	if (tmp->type == OPERATOR && node->type <= OPERATOR)
	{
		tmp->left = node;
		node->back = tmp;
		if ((*sort)->type != LOGIC)
			*sort = tmp;
	}
	else if (node->type == CMD)
	{
		tmp->left = *sort;
		(*sort)->back = tmp;
		*sort = tmp;
	}
	else if (node->type <= tmp->type)
	{
		tmp->left = node;
		node->back = tmp;
		if ((*sort)->type != LOGIC)
			*sort = tmp;
	}
	// 	insert_between(node, tmp);
	// else if (node->right->type == CMD)
	// 	insert_end(node, tmp);


	// t_ast	*or;
	//
	// or = node;
	// while (or && tmp->type >= or->type && or->back)
	// 	or = or->back;
	// if (!node->right && node->type != CMD)
	// {
	// 	node->right = tmp;
	// 	tmp->back = node;
	// }
	// else if (node->type == CMD || or == NULL)
	// {
	// 	tmp->left = *sort;
	// 	(*sort)->back = tmp;
	// 	*sort = tmp;
	// }
	// else if (node->type < tmp->type)
	// 	insert_between(node, tmp);
	// else if (node->right->type == CMD && or)
	// 	insert_end(node, tmp);
}
