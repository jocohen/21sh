/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/19 20:03:15 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"



static void			read_sort_descent(t_ast *sort, int w)
{
	t_ast	*tmp;
	int		i;
	tmp = sort;
	if (w)
		return ;
	ft_printf("A GAUCHE  \n");
	while (tmp->left)
	{
		ft_printf("type= %d\n", tmp->type);
		i = 0;
		while (tmp->input[i])
		{
			ft_printf("input[%d]: %s\n", i, tmp->input[i]);
			i += 1;
		}
		tmp->print = 1;
		tmp = tmp->left;
	}
	ft_printf("\ntype= %d\n", tmp->type);
	i = 0;
	while (tmp->input[i])
	{
		ft_printf("input[%d]: %s\n", i, tmp->input[i]);
		i += 1;
	}
	tmp->print = 1;
	while (tmp)
	{
		if (tmp->left && tmp->left->print == 0)
		{
			tmp = tmp->left;
			ft_printf("A GAUCHE DE %s  type= %d\n", tmp->back->input[0], tmp->type);
			i = 0;
			while (tmp->input[i])
			{
				ft_printf("input[%d]: %s\n", i, tmp->input[i]);
				i += 1;
			}
			tmp->print = 1;
		}
		else if (tmp->right && tmp->right->print == 0)
		{
			tmp = tmp->right;
			ft_printf("A DROITE DE %s type= %d\n", tmp->back->input[0], tmp->type);
			i = 0;
			while (tmp->input[i])
			{
				ft_printf("input[%d]: %s\n", i, tmp->input[i]);
				i += 1;
			}
			tmp->print = 1;
		}
		else
			tmp = tmp->back;
	}
}



static void		reinit_print(t_ast *lst)
{
	t_ast	*tmp;
	tmp = lst;
	while (tmp)
	{
		tmp->print = 0;
		tmp = tmp->next;
	}
}

// static void		read_sort(t_ast *sort)
// {
// 	t_ast	*tmp;
// 	t_ast	*save;
// 	int		i;
// 	tmp = sort;
// 	save = NULL;
// 	i = 0;
// 	while (tmp->left)
// 		tmp = tmp->left;
// 	while (tmp)
// 	{
// 		(tmp->print == 0) ? ft_printf("\ntype = %d\n", tmp->type) : 0;
// 		i = 0;
// 		while (tmp->input[i] && tmp->print == 0)
// 		{
// 			ft_printf("input[%d]: %s\n", i, tmp->input[i]);
// 			i += 1;
// 		}
// 		tmp->print = 1;
// 		if (tmp->right && tmp->right->print == 0)
// 		{
// 			if (tmp->right->type != CMD)
// 			{
// 				tmp = tmp->right;
// 				while (tmp->left)
// 					tmp = tmp->left;
// 				(tmp->print == 0) ? ft_printf("\ntype = %d\n", tmp->type) : 0;
// 				i = 0;
// 				while (tmp->input[i] && tmp->print == 0)
// 				{
// 					ft_printf("input[%d]: %s\n", i, tmp->input[i]);
// 					i += 1;
// 				}
// 				tmp->print = 1;
// 			}
// 			else
// 			{
// 				(tmp->right->print == 0) ? ft_printf("\ntype = %d\n",
// 				tmp->right->type) : 0;
// 				i = 0;
// 				while (tmp->right->input[i] && tmp->right->print == 0)
// 				{
// 					ft_printf("input[%d]: %s\n", i, tmp->right->input[i]);
// 					i += 1;
// 				}
// 				tmp->right->print = 1;
// 			}
// 		}
// 		tmp = tmp->back;
// 	}
// }











static t_ast	*get_available_node(t_ast **sort)
{
	t_ast	*tmp;

	tmp = *sort;
	// if (tmp && (ft_strcmp(tmp->input[0], "||") == 0
	// || ft_strcmp(tmp->input[0], "&&") == 0))
	if (tmp && (tmp->type == OPERATOR || tmp->type == LOGIC))
	{
		if (tmp->right)
		{
			while (tmp->right && tmp->right->type != CMD)
				tmp = tmp->right;
			return (tmp);
		}
	}
	return (tmp);
}

static void		link_new_node(t_ast **sort, t_ast *tmp, t_ast *node)
{
	t_ast	*or;

	or = node;
	while (or && tmp->type >= or->type)
		or = or->back;
	if (!node->right && node->type != CMD)
	{
		node->right = tmp;
		tmp->back = node;
	}
	else if (node->type == CMD || or == NULL)
	{
		tmp->left = *sort;
		(*sort)->back = tmp;
		*sort = tmp;
	}
	else if (node->type < tmp->type)
	{
		tmp->left = node;
		tmp->back = node->back;
		node->back->right = tmp;
		node->back = tmp;
	}
	else if (node->right->type == CMD && or)
	{
		tmp->left = node->right;
		node->right->back = tmp;
		tmp->back = node;
		node->right = tmp;
	}
}

static void		sort_ast(t_ast *lst, t_ast **sort)
{
	t_ast	*tmp;
	t_ast	*node;

	*sort = lst;
	tmp = lst->next;
	while (tmp)
	{
		node = get_available_node(sort);
		if (tmp->type == LOGIC)
		{
			tmp->left = *sort;
			(*sort)->back = tmp;
			*sort = tmp;
		}
		else if (tmp->type != CMD)
			link_new_node(sort, tmp, node);
		else if (tmp->type == CMD)
		{
			(!node->left) ? node->left = tmp : 0;
			(!node->right) ? node->right = tmp : 0;
			tmp->back = node;
		}
		tmp = tmp->next;
	}
}

void			parser(char **input, t_ast *lst, t_env **lst_env,
				t_alloc **alloc)
{
	int		i;
	t_ast	*sort;

	sort = NULL;
	if (ft_error_parse_redir(input) == 1)
	{
		delete_str_tab(input);
		g_ret[0] = 1;
		return ;
	}
	fill_ast(input, &lst);
	sort = lst;
	while (sort)
	{
		i = -1;
		while (sort->input[++i])
			if (convert_quote(&(sort->input[i]), lst_env, alloc) == -1)
				return ;
		sort = sort->next;
	}
	sort_ast(lst, &sort);

	ft_printf("\nAST:\n");
	read_sort_descent(sort, 0);
	reinit_print(lst);
	ft_printf("END READ\n\n");

	(*alloc)->ast = &lst;
	analyzer(sort, lst_env, alloc);
	(input) ? delete_str_tab(input) : 0;
	del_lst_ast(&lst);
}
