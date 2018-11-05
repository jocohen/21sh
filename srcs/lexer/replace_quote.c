/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:07 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/05 14:35:36 by tcollard         ###   ########.fr       */
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

static void	replace_env_var(char **str, int i)
{
	int			save;
	static char	value[];

	save = 0;
	while (*str[i] != '$')
	{
		if (*str[i] == '$')
		{
			while (*str[i] && ft_isspace(*str[i]) == 0)
			{

				i += 1;
			}
		}
		i += 1;
	}
}

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
	{
		if (*s[*i] == '$')
			replace_env_var(s, *i);
		*i += 1;
	}
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
