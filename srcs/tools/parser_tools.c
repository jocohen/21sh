/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 11:06:56 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/16 18:42:32 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

t_ast	*create_new_elem(t_ast **lst)
{
	t_ast	*new;

	if (!(new = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	new->type = NO_TYPE;
	new->value = NULL;
	new->opt = NULL;
	new->content = NULL;
	new->back_quote = NULL;
	new->next = NULL;
	new->prev = NULL;
	(*lst == NULL) ? *lst = new : 0;
	return (new);
}

t_ast	*get_last_elem(t_ast **lst)
{
	t_ast *elem;

	elem = *lst;
	while (elem->next != NULL)
		elem = elem->next;
	return (elem);
}

t_ast	*add_new_elem(t_ast **lst)
{
	t_ast	*end;
	t_ast	*new;

	new = create_new_elem(lst);
	end = get_last_elem(lst);
	end->next = new;
	new->prev = end;
	return (new);
}
