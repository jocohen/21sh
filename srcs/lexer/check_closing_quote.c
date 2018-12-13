/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closing_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:25:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/13 18:40:02 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	check_opening_quote(char **str, t_alloc *alloc)
{
	int	i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		if (ft_isquote((*str)[i]) == 1)
			find_closing(str, &i, alloc);
		i += 1;
	}
}

void	find_closing(char **str, int *i, t_alloc *alloc)
{
	char	c;
	char	*tmp;
	char	*save;

	tmp = NULL;
	save = NULL;
	c = (*str)[*i];
	*i += 1;
	while ((*str)[*i] && (*str)[*i] != c)
		*i += 1;
	if ((*str)[*i] == c)
		return ;
	else
	{
		tmp = missing_quote_prompt(c, alloc);
		save = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(save, tmp);
		free(save);
		free(tmp);
		*i = ft_strlen(*str);
	}
}
