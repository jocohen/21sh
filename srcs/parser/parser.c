/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/26 09:00:16 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	read_lst(t_ast *lst, int active)
{
	t_ast	*tmp;
	int		x;
	int		i;

	i = 0;
	tmp = lst;
	if (active == 0)
		return ;
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

static void			read_sort_descent(t_ast *sort, int active)
{
	t_ast	*tmp;
	int		i;

	tmp = sort;
	if (active == 0)
		return ;
	while (tmp->left)
	{
		ft_printf("\ntype= %d\n", tmp->type);
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
			ft_printf("\ntype= %d\n", tmp->type);
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
			ft_printf("\ntype= %d\n", tmp->type);
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

static void		reinit_print(t_ast *lst, int active)
{
	t_ast	*tmp;

	tmp = lst;
	if (active == 0)
		return ;
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

static void		clean_tab_and_ast(char **input, t_ast *lst)
{
	// (void)input;
	delete_str_tab(input);
	del_lst_ast(&lst);

}

void			parser(char **input, t_ast *lst, t_env **lst_env,
				t_alloc **alloc)
{
	int		i;
	t_ast	*sort;


//CHECK PARSE ERROR IF IT STILL AVAILABLE FOR NEW LEXER
	if (ft_error_parse_redir(input) == 1)
	{
		g_ret[0] = 1;
		return ;
	}
	fill_ast(input, &lst, 0);
	// while (1) {}

	// ft_printf("READ LIST\n");
	read_lst(lst, 0);
	// ft_printf("\n\nEND\n");

	sort = lst;
	i = 0;
	// ft_putstr(ANSI_RED);
	// ft_printf("input =");
	// while (input[i])
	// 	ft_printf(" %s", input[i++]);
	// ft_printf("\n");
	// ft_putstr(ANSI_RESET);
	while (sort)
	{
		i = -1;
		while (sort->input[++i])
			if (convert_quote(&(sort->input[i]), lst_env, alloc) == -1)
			{
				clean_tab_and_ast(input, lst);
				return ;
			}
		sort = sort->next;
	}
	sort_ast(lst, &sort);
	read_sort_descent(sort, 0);

	// ft_printf("READ AST:\n\n");
	// read_sort_descent(sort);
	// ft_printf("END MOTHA FUCKA\n\n");
	reinit_print(lst, 0);
	(*alloc)->ast = &lst;
	(complete_heredoc(lst, alloc)) ? analyzer(sort, lst_env, alloc) : 0;
	clean_tab_and_ast(input, lst);
}
