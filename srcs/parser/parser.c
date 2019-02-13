/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/13 15:17:03 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**static void	read_lst(t_ast *lst)
**{
**	t_ast	*tmp;
**	int		x;
**	int		i;
**	i = 0;
**	tmp = lst;
**	while (tmp)
**	{
**		ft_printf("Elem %d ___ type: %d\n", i, tmp->type);
**		x = 0;
**		while (tmp->input[x])
**		{
**			ft_printf("tmp->input[%d]: %s\n", x, tmp->input[x]);
**			x += 1;
**		}
**		ft_printf("\n\n");
**		tmp = tmp->next;
**		i += 1;
**	}
**}
*/

static t_ast	*get_available_node(t_ast **sort)
{
	t_ast	*tmp;

	tmp = *sort;
	if (tmp && (ft_strcmp(tmp->input[0], "||") == 0
	|| ft_strcmp(tmp->input[0], "&&") == 0))
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
	while (or && ft_strcmp(or->input[0], "||") != 0
	&& ft_strcmp(or->input[0], "&&") != 0)
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
		if (ft_strcmp(tmp->input[0], "||") == 0
		|| ft_strcmp(tmp->input[0], "&&") == 0)
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

/*
**static void			read_sort_descent(t_ast *sort)
**{
**	t_ast	*tmp;
**	int		i;
**	tmp = sort;
**	while (tmp->left)
**	{
**		ft_printf("\ntype= %d\n", tmp->type);
**		i = 0;
**		while (tmp->input[i])
**		{
**			ft_printf("input[%d]: %s\n", i, tmp->input[i]);
**			i += 1;
**		}
**		tmp->print = 1;
**		tmp = tmp->left;
**	}
**	ft_printf("\ntype= %d\n", tmp->type);
**	i = 0;
**	while (tmp->input[i])
**	{
**		ft_printf("input[%d]: %s\n", i, tmp->input[i]);
**		i += 1;
**	}
**	tmp->print = 1;
**	while (tmp)
**	{
**		if (tmp->left && tmp->left->print == 0)
**		{
**			tmp = tmp->left;
**			ft_printf("\ntype= %d\n", tmp->type);
**			i = 0;
**			while (tmp->input[i])
**			{
**				ft_printf("input[%d]: %s\n", i, tmp->input[i]);
**				i += 1;
**			}
**			tmp->print = 1;
**		}
**		else if (tmp->right && tmp->right->print == 0)
**		{
**			tmp = tmp->right;
**			ft_printf("\ntype= %d\n", tmp->type);
**			i = 0;
**			while (tmp->input[i])
**			{
**				ft_printf("input[%d]: %s\n", i, tmp->input[i]);
**				i += 1;
**			}
**			tmp->print = 1;
**		}
**		else
**			tmp = tmp->back;
**	}
**}
*/

/*
**static void		reinit_print(t_ast *lst)
**{
**	t_ast	*tmp;
**	tmp = lst;
**	while (tmp)
**	{
**		tmp->print = 0;
**		tmp = tmp->next;
**	}
**}
**
**static void		read_sort(t_ast *sort)
**{
**	t_ast	*tmp;
**	t_ast	*save;
**	int		i;
**	tmp = sort;
**	save = NULL;
**	i = 0;
**	while (tmp->left)
**		tmp = tmp->left;
**	while (tmp)
**	{
**		(tmp->print == 0) ? ft_printf("\ntype = %d\n", tmp->type) : 0;
**		i = 0;
**		while (tmp->input[i] && tmp->print == 0)
**		{
**			ft_printf("input[%d]: %s\n", i, tmp->input[i]);
**			i += 1;
**		}
**		tmp->print = 1;
**		if (tmp->right && tmp->right->print == 0)
**		{
**			if (tmp->right->type != CMD)
**			{
**				tmp = tmp->right;
**				while (tmp->left)
**					tmp = tmp->left;
**				(tmp->print == 0) ? ft_printf("\ntype = %d\n", tmp->type) : 0;
**				i = 0;
**				while (tmp->input[i] && tmp->print == 0)
**				{
**					ft_printf("input[%d]: %s\n", i, tmp->input[i]);
**					i += 1;
**				}
**				tmp->print = 1;
**			}
**			else
**			{
**				(tmp->right->print == 0) ? ft_printf("\ntype = %d\n",
**				tmp->right->type) : 0;
**				i = 0;
**				while (tmp->right->input[i] && tmp->right->print == 0)
**				{
**					ft_printf("input[%d]: %s\n", i, tmp->right->input[i]);
**					i += 1;
**				}
**				tmp->right->print = 1;
**			}
**		}
**		tmp = tmp->back;
**	}
**}
*/

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
	(*alloc)->ast = &lst;
	analyzer(sort, lst_env, alloc);
	(input) ? delete_str_tab(input) : 0;
	del_lst_ast(&lst);
}

/*
**ft_printf("\n== READ LIST ==\n\n");
**read_lst(lst);
**ft_printf("\n=== READ SORT ==\n\n");
**read_sort(sort);
**reinit_print(lst);
**ft_printf("\n=== READ SORT DESCENT ==\n\n");
**read_sort_descent(sort);
*/
