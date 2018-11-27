/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/27 15:38:42 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
** static void	read_lst(t_ast *lst)
** {
** 	t_ast	*tmp;
** 	int		x;
** 	int		i;
**
** 	i = 0;
** 	tmp = lst;
** 	while (tmp)
** 	{
** 		ft_printf("Elem %d ___ type: %d\n", i, tmp->type);
** 		x = 0;
** 		while (tmp->input[x])
** 		{
** 			ft_printf("tmp->input[%d]: %s\n", x, tmp->input[x]);
** 			x += 1;
** 		}
** 		ft_printf("\n\n");
** 		tmp = tmp->next;
** 		i += 1;
** 	}
** }
*/

void		parser(char **input, t_ast *lst, t_env *lst_env)
{
	int		i;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	if (ft_error_parse_redir(input) == 1)
	{
		delete_str_tab(input);
		return ;
	}
	fill_ast(input, &lst);
	analyzer(lst, lst_env);
	if (input)
		delete_str_tab(input);
	if (lst)
		del_lst_ast(&lst);
}

/*
**	read_lst(lst); (between fillast and analyzer)
*/
