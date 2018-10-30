/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:43:14 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/30 19:11:57 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int		check_operator(char *s, int *i, unsigned int *nb_word)
{
	char	c;

	c = '\0';
	if ((s[*i] == '&' && s[*i + 1] != '<' && s[*i + 1] != '>') || s[*i] == '|')
	{
		c = s[*i];
		while (s[*i] == c)
			*i += 1;
		*nb_word += (s[*i] && ft_isspace(s[*i]) == 0) ? 2 : 1;
		return (1);
	}
	return (0);
}

void	position_operator(char const *s, int *i, int wn, int *iw)
{
	char	c;
	int		x;

	c = '\0';
	x = 0;
	if ((s[*i] == '&' && s[*i + 1] != '<' && s[*i + 1] != '>') || s[*i] == '|')
	{
		c = s[*i];
		while (s[*i + x] == c)
			x += 1;
		if ((*iw += 1) == wn)
			return ;
		if (s[*i + x] && ft_isspace(s[*i + x] == 0))
		{
			*iw += 1;
			*i += x;
		}
	}
}
