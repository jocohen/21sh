/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:40:15 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:43:05 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int		x;

	if (!s1 || !s2)
		return (0);
	x = ft_strncmp(s1, s2, n);
	if (!x)
		return (1);
	return (0);
}
