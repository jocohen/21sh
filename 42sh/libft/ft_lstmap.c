/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:44:44 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:21:29 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	applic(t_list *lst, t_list *(*f)(t_list *elem),
		t_list *output, t_list *t)
{
	t_list	*previous;

	while (lst->next)
	{
		lst = lst->next;
		previous = output;
		output = output->next;
		if (!(t = ft_lstnew(lst->content, lst->content_size)))
			return ;
		t = f(lst);
		if (!(output = ft_lstnew(t->content, t->content_size)))
			return ;
		previous->next = output;
		free(t);
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*output;
	t_list	*t;
	t_list	*start;

	if (!lst)
		return (0);
	if (!(t = ft_lstnew(lst->content, lst->content_size)))
		return (0);
	t = f(lst);
	if (!(output = ft_lstnew(t->content, t->content_size)))
		return (0);
	free(t);
	start = output;
	applic(lst, f, output, t);
	return (start);
}
