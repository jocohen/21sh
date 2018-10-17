/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:07 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/01 11:41:09 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
 ** In double quote
 ** check for env var
*/

/*
 ** In back quote
 ** execute commande
*/

void	remove_quote(char **s, int *i)
{
	char	*sub;
	char	*str;
	char	quote;
	int		save;

	sub = NULL;
	str = NULL;
	quote = (*s)[(*i)++];
	save = *i;
	while ((*s)[*i] && (*s)[*i] != quote)
		*i += 1;
	if (quote == '\'')
		sub = ft_strsub(*s, save, *i - save);
	else if (quote == '"')
	{
		sub = ft_strsub(*s, save, *i - save);
	}
	else if (quote == '`')
	{
		sub = ft_strsub(*s, save, *i - save);
	}
	(sub != NULL) ? ft_insert(s, sub, save - 1) : 0;
}

void	convert_quote(char **s)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{
		if (ft_isquote((*s)[i]) == 1)
		{
			remove_quote(s, &i);
			i -= 2;
		}
		else
			i += 1;
	}
}
