/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2019/03/01 22:59:20 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	lst_r(t_ast *lst)
{
	t_ast    *tmp;
    int        x;
    int        i;

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

void			read_lst(t_ast *sort)
{
	t_ast	*tmp;
	int		i;
	tmp = sort;
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

void		reinit_print(t_ast *lst)
{
	t_ast	*tmp;
	tmp = lst;
	while (tmp)
	{
		tmp->print = 0;
		tmp = tmp->next;
	}
}


static t_ast	*get_available_node(t_ast **sort)
{
	t_ast	*tmp;

	tmp = *sort;
	if (tmp && tmp->type == LOGIC)
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
			if (!node->left)
				node->left = tmp;
			else if (!node->right)
				node->right = tmp;
			tmp->back = node;
		}
		tmp = tmp->next;
	}
}

static void		clean_tab_and_ast(char **input, t_ast *lst)
{
	delete_str_tab(input);
	del_lst_ast(&lst);
}

void			parser(char **input, t_ast *lst, t_env **lst_env,
				t_alloc **alloc)
{
	int		i;
	t_ast	*sort;

	if (ft_error_parse_redir(input) == 1)
	{
		g_ret[0] = 1;
		return ;
	}
	fill_ast(input, &lst, 0, -1);
	lst_r(lst);
	if (check_error_lst(lst) == 1)
		return (clean_tab_and_ast(input, lst));
	sort = lst;
	i = 0;
	ft_putstr(ANSI_BLUE);
	ft_printf("cmd =");
	while (input[i])
		ft_printf(" %s", input[i++]);
	ft_printf("\n");
	ft_putstr(ANSI_RESET);
	while (sort)
	{
		i = -1;
		while (sort->input[++i])
			if (convert_quote(&(sort->input[i]), lst_env, alloc) == -1)
				return (clean_tab_and_ast(input, lst));
		sort = sort->next;
	}
	sort_ast(lst, &sort);
	// read_lst(sort);
	// reinit_print(lst);
	(*alloc)->ast = &lst;
	(complete_heredoc(lst, alloc)) ? analyzer(sort, lst_env, alloc) : 0;
	clean_tab_and_ast(input, lst);
}
