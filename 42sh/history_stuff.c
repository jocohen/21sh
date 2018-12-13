/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:02:45 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/12 18:58:27 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			search_cmd_common(const char *s, const char *sch)
{
	size_t	y;
	size_t	len;

	y = 0;
	len = ft_strlen(sch);
	while (s && s[y] && sch[y] && s[y] == sch[y])
		y += 1;
	if (y == len)
		return (1);
	return (0);
}

t_historic	*ft_new_cmd_hist(void)
{
	t_historic	*lst;

	if (!(lst = (t_historic*)malloc(sizeof(t_historic))))
		return (0);
	lst->origin = 0;
	lst->modif = 0;
	lst->next = 0;
	lst->prev = 0;
	return (lst);
}

void		reset_hist(t_historic *tmp)
{
	while (tmp)
	{
		ft_memdel((void **)&(tmp->modif));
		tmp = tmp->prev;
	}
}

int			ft_del_hist(t_historic **fp)
{
	t_historic	*tmp;

	while ((*fp)->prev)
		(*fp) = (*fp)->prev;
	while ((*fp))
	{
		tmp = (*fp)->next;
		ft_memdel((void **)&((*fp)->origin));
		ft_memdel((void **)&((*fp)->modif));
		ft_memdel((void **)fp);
		(*fp) = tmp;
	}
	return (0);
}
