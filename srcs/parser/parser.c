/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/22 13:26:15 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

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
	fill_ast(input, &lst, 0);
	sort = lst;
	while (sort)
	{
		i = -1;
		while (sort->input[++i])
			if (convert_quote(&(sort->input[i]), lst_env, alloc) == -1)
			{
				delete_str_tab(input);
				del_lst_ast(&lst);
				return ;
			}
		sort = sort->next;
	}
	sort_ast(lst, &sort);
	(*alloc)->ast = &lst;
	i = 0;
	ft_putstr(ANSI_BLUE);
	ft_printf("cmd = |");
	while (lst->input[i])
	{
		ft_printf("%s ", lst->input[i++]);
	}
	ft_printf("|\n");
	ft_putstr(ANSI_RESET);
	(complete_heredoc(lst, alloc)) ? analyzer(sort, lst_env, alloc) : 0;
	delete_str_tab(input);
	del_lst_ast(&lst);
}
