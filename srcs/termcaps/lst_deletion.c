/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_deletion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:14:04 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/19 10:45:39 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int		lst_deletion(t_list **fp)
{
	t_list	*tmp;

	while ((*fp))
	{
		tmp = (*fp)->next;
		ft_memdel((void **)&((*fp)->content));
		(*fp)->content_size = 0;
		ft_memdel((void **)fp);
		(*fp) = tmp;
	}
	return (0);
}
