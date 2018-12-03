/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/03 17:02:56 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static void	read_lst(t_ast *lst)
{
	t_ast	*tmp;
	int		x;
	int		i;
	i = 0;
	tmp = lst;
	while (tmp)
	{
		ft_printf("Elem %d ___ type: %d\n", i, tmp->type);
		x = 0;
		while (tmp->input[x])
		{
			ft_printf("tmp->input[%d]: %s\n", x, tmp->input[x]);
			x += 1;
		}
		ft_printf("\n\n");
		tmp = tmp->next;
		i += 1;
	}
}

// static t_ast	*get_last_empty_node(t_ast *sort)
// {
// 	t_ast	*tmp;
//
// 	tmp = sort;
// 	if (tmp->right && tmp->right->type != CMD)
// 		tmp = tmp->right;
// 	while (tmp->left && tmp->left->type != CMD)
// 		tmp = tmp->left;
// 	return (tmp);
// }

// static void		sort_ast(t_ast *lst, t_ast **sort)
// {
// 	t_ast	*tmp;
// 	t_ast	*node;
//
// 	node = NULL;
// 	*sort = lst;
// 	tmp = lst->next;
// 	while (tmp)
// 	{
// 		node = get_last_empty_node(*sort);
// 		if (node->type == CMD)
// 		{
// 			node->back = tmp;
// 			tmp->left = node;
// 			*sort = tmp;
// 		}
// 		else if (node->type != CMD && !node->left)
// 		{
// 			node->left = tmp;
// 			tmp->back = node;
// 		}
// 		else if (node->type != CMD && !node->right)
// 		{
// 			node->right = tmp;
// 			tmp->back = node;
// 		}
// 		tmp = tmp->next;
// 	}
// }

static void		add_right(t_ast *elem, t_ast **sort)
{
	t_ast	*tmp;

	tmp = *sort->right;
	while (tmp->left)
		tmp = tmp->left;
	if (tmp->type != CMD)
	{
		tmp->left = elem;
		elem->back = tmp;
	}
}

static void		add_left(t_ast *elem, t_ast **sort)
{
	t_ast *tmp;

	tmp = *sort->left;
	while (tmp && tmp->left && tmp->left != CMD)
		tmp = tmp->left;
	if (tmp && tmp->left)
}

static void		sort_ast(t_ast *lst, t_ast **sort)
{
	t_ast	*tmp;

	*sort = lst;
	tmp = lst->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->input[0], "||") != 0)
		{
			if (ft_strcmp(*sort->input[0], "||") == 0)
			{
				// add_right(tmp, sort);
			}
			else
			{
				// go left;
			}
		}
		else if (ft_strcmp(tmp->input[0], "||") == 0)
		{
			tmp->left = *sort;
			*sort->back = tmp;
			*sort = tmp;
		}
		tmp = tmp->next;
	}
}

static void		read_sort(t_ast *sort)
{
	t_ast	*tmp;
	int		i;

	i = 0;
	tmp = sort;
	while (tmp->left)
		tmp = tmp->left;
	while (tmp)
	{
		if (tmp->left)
		{
			ft_printf("\ntype: %d\n", tmp->left->type);
			i = 0;
			while (tmp->left->input[i])
			{
				ft_printf("input[%d]: %s\n", i, tmp->left->input[i]);
				i += 1;
			}
		}
		if (tmp->right)
		{
			ft_printf("\ntype: %d\n", tmp->right->type);
			i = 0;
			while (tmp->right->input[i])
			{
				ft_printf("input[%d]: %s\n", i, tmp->right->input[i]);
				i += 1;
			}
		}
		if (tmp->back)
			tmp = tmp->back;
		else
			break ;
	}
	// ft_printf("IN HERE!\n");
	ft_printf("\ntype: %d\n", tmp->type);
	i = 0;
	while (tmp->input[i])
	{
		ft_printf("input[%d]: %s\n", i, tmp->input[i]);
		i += 1;
	}
}

void			parser(char **input, t_ast *lst, t_env *lst_env)
{
	int		i;
	t_ast	*sort;

	(void)lst_env;

	i = 0;
	sort = NULL;
	if (ft_error_parse_redir(input) == 1)
	{
		delete_str_tab(input);
		return ;
	}
	fill_ast(input, &lst);
	sort_ast(lst, &sort);
	ft_printf("SORT type = %d sort input[0]: %s\n", sort->type, sort->input[0]);
	ft_printf("\n== READ LIST ==\n\n");
	read_lst(lst);
	ft_printf("\n=== READ SORT ==\n\n");
	read_sort(sort);
	// analyzer(lst, lst_env);
	// if (input)
	// 	delete_str_tab(input);
	// del_lst_ast(&lst);
}
