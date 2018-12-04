/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/04 16:25:37 by tcollard         ###   ########.fr       */
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

static t_ast		*get_available_node(t_ast **sort)
{
	t_ast	*tmp;

	tmp = *sort;
	// ft_printf("OK\n");
	if (tmp && ft_strcmp(tmp->input[0], "||") == 0)
	{
		// ft_printf("OK2\n");
		if (tmp->right)
		{
			while (tmp->right && tmp->right->type != CMD)
				tmp = tmp->right;
			return (tmp);
		}
	}
	// ft_printf("OK end\n");
	return (tmp);
}

static void		sort_ast(t_ast *lst, t_ast **sort)
{
	t_ast	*tmp;
	t_ast	*node;

	node = NULL;
	*sort = lst;
	tmp = lst->next;
	while (tmp)
	{
		ft_printf("tmp input: %s\n", tmp->input[0]);
		node = get_available_node(sort);
		ft_printf("node input: %s\n", node->input[0]);
		if (ft_strcmp(tmp->input[0], "||") == 0)
		{
			tmp->left = *sort;
			(*sort)->back = tmp;
			*sort = tmp;	
		}
		else if (tmp->type != CMD)
		{
			tmp->left = *sort;
			(*sort)->back = tmp;
			*sort = tmp;
		}
		else if (tmp->type == CMD)
		{
			if (!node->left)
				node->left = tmp;
			else if (!node->right)
				node->right = tmp;
			tmp->back = node;
		}
		tmp = tmp->next;
	}
}

static void		read_sort(t_ast *sort)
{
	t_ast	*tmp;
	t_ast	*save;
	int		i;

	tmp = sort;
	save = NULL;
	i = 0;
	while (tmp->left)
		tmp = tmp->left;
	while (tmp)
	{
		(tmp->print == 0) ? ft_printf("\ntype = %d\n", tmp->type) : 0;
		i = 0;
		while (tmp->input[i] && tmp->print == 0)
		{
			ft_printf("input[%d]: %s\n", i, tmp->input[i]);
			i += 1;
		}
		tmp->print = 1;
		if (tmp->right && tmp->right->print == 0)
		{
			if (tmp->right->type != CMD)
			{
				tmp = tmp->right;
				while (tmp->left)
					tmp = tmp->left;
				(tmp->print == 0) ? ft_printf("\ntype = %d\n", tmp->type) : 0;
				i = 0;
				while (tmp->input[i] && tmp->print == 0)
				{
					ft_printf("input[%d]: %s\n", i, tmp->input[i]);
					i += 1;
				}
				tmp->print = 1;
			}
			else
			{
				(tmp->right->print == 0) ? ft_printf("\ntype = %d\n", tmp->right->type) : 0;
				i = 0;
				while (tmp->right->input[i] && tmp->right->print == 0)
				{
					ft_printf("input[%d]: %s\n", i, tmp->right->input[i]);
					i += 1;
				}
				tmp->right->print = 1;
			}
		}
		tmp = tmp->back;
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
	// ft_printf("SORT type = %d sort input[0]: %s\n", sort->type, sort->input[0]);
	ft_printf("\n== READ LIST ==\n\n");
	sort_ast(lst, &sort);
	read_lst(lst);
	ft_printf("\n=== READ SORT ==\n\n");
	read_sort(sort);
	// analyzer(lst, lst_env);
	// if (input)
	// 	delete_str_tab(input);
	// del_lst_ast(&lst);
}
