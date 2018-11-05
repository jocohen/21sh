/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/05 11:16:03 by tcollard         ###   ########.fr       */
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

void	parser(char **input, t_ast *lst, char **tab_env)
{
	int		i;
	t_ast	*tmp;

	int	x;
	x = 0;

	i = 0;
	tmp = NULL;
	(void)tab_env;
	(void)lst;
	if (ft_error_parse_redir(input) == 1)
	{
		delete_str_tab(input);
		// while (input[i])
		// {
		// 	free(input[i]);
		// 	i += 1;
		// }
		// free(input);
		return ;
	}
	fill_ast(input, &lst);
	read_lst(lst);
	// while (input[i])
	// {
	// 	ft_printf("input[%d]: %s\n", i, input[i]);
	// 	free(input[i]);
	// 	i += 1;
	// }
	// free(input);
	// i = 0;
	// tmp = lst;
	// while (tmp != NULL)
	// {
	// 	tmp = tmp->next;
	// 	i += 1;
	// }
	// analyzer(lst, tab_env);
}
