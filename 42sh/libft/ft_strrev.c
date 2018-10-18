/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 20:51:33 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/31 04:57:50 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrev(char *str)
{
	int		len;
	int		x;
	char	tmp;

	len = ft_strlen(str) - 1;
	x = 0;
	while (x < len)
	{
		tmp = str[x];
		str[x] = str[len];
		str[len] = tmp;
		len--;
		x++;
	}
	return (str);
}
