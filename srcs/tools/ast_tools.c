/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:49:35 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/28 17:25:18 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	fill_last_elem(char **s, int i, int save, t_ast *new)
{
	if (new->type == NO_TYPE)
		fill_input(s, i, save, new);
	else if (i != save)
		add_input_prev_cmd(s, i, save, new);
}

void	link_new_node(t_ast **sort, t_ast *tmp, t_ast *node)
{
	t_ast	*h_node;

	h_node = node;
	if ((*sort)->type == LOGIC)
	{
		if (node->right)
		{
			tmp->left = node->right;
			node->right->back = tmp;
		}
		node->right = tmp;
		tmp->back = node;
	}
	else if (tmp->type != HEREDOC)
	{
		tmp->left = node;
		node->back = tmp;
		((*sort)->type != LOGIC) ? *sort = tmp : 0;
	}
	else
	{
		tmp->left = *sort;
		(*sort)->back = tmp;
		*sort = tmp;
	}
}

void	add_input_prev_cmd(char **s, int end, int start, t_ast *elem)
{
	char	**tmp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (elem->back && elem->type != CMD)
		elem = elem->back;
	while (elem->input[len])
		len += 1;
	len += end - start;
	(!(tmp = (char**)malloc(sizeof(char*) * (len + 1)))) ? ft_exit_malloc() : 0;
	while (elem->input[i])
	{
		tmp[i] = ft_strdup(elem->input[i]);
		i += 1;
	}
	while (i < len)
	{
		tmp[i] = ft_strdup(s[start++]);
		i += 1;
	}
	tmp[i] = NULL;
	delete_str_tab(elem->input);
	elem->input = tmp;
}
