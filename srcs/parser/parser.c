/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/24 15:40:05 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

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
	fill_ast(input, &lst);
	// ft_printf("lst->input[0]: %s\n", lst->input[0]);
	tmp = lst;
	while (tmp)
	{
		ft_printf("Elem %d:\ntype: %d\n", i, tmp->type);
		x = 0;
		while (tmp->input[x] != NULL)
		{
			ft_printf("tmp->input[%d]: %s\n", x, tmp->input[x]);
			x += 1;
		}
		tmp = tmp->next;
		i += 1;
	}
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
