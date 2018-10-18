/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:15:25 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:21:37 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*output;

	if (!(output = (t_list *)malloc(sizeof(t_list))))
		return (0);
	if (content)
	{
		if (!(output->content = (void *)malloc(content_size)))
			return (0);
		ft_memcpy(output->content, content, content_size);
		output->content_size = content_size;
	}
	else
	{
		output->content = 0;
		output->content_size = 0;
	}
	output->next = 0;
	return (output);
}
