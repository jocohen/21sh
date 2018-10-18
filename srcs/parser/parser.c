/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:48:48 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/17 17:43:31 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
** ft_printf("Elem[%d]:\n->type: %d\n->value: %s\n->opt: %s\n->content: %s\n\n",
**	i, tmp->type, tmp->value, tmp->opt, tmp->content);
*/

void	parser(char **input, t_ast *lst, char **tab_env)
{
	int		i;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	while (input[i])
	{
		fill_ast(input[i], &lst);
		free(input[i]);
		i += 1;
	}
	free(input);
	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i += 1;
	}
	analyzer(lst, tab_env);
}
