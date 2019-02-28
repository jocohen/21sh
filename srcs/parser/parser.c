/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/28 12:05:30 by tcollard         ###   ########.fr       */
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
			(!node->left) ? node->left = tmp : 0;
			(!node->right) ? node->right = tmp : 0;
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
	fill_ast(input, &lst, 0);
	read_lst(lst, 1);
	sort = lst;
	i = 0;
	while (sort)
	{
		i = -1;
		while (sort->input[++i])
			if (convert_quote(&(sort->input[i]), lst_env, alloc) == -1)
				return (clean_tab_and_ast(input, lst));
		sort = sort->next;
	}
	sort_ast(lst, &sort);
	(*alloc)->ast = &lst;
	(complete_heredoc(lst, alloc)) ? analyzer(sort, lst_env, alloc) : 0;
	clean_tab_and_ast(input, lst);
}
