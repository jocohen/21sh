/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:07 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/06 10:48:59 by tcollard         ###   ########.fr       */
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

/*
**	Repclace env var:
**		1 - Get the key and Value
**		2 - rm key from str input
**		3 - insert value at the good place
*/

static void	replace_str(char **str, char *insert, int pos)
{
	char *begin;
	char *end;
	char *tmp;

	if (!*str)
		*str = ft_strdup(insert);
	else
	{
		begin = ft_strsub(*str, 0, pos);
		end = ft_strsub(*str, pos, ft_strlen(*str));
		free(*str);
		tmp = ft_strjoin(begin, insert);
		*str = ft_strjoin(tmp, end);
		free(tmp);
		free(begin);
		free(end);
	}
}

static int	replace_env_var(char **str, int i, char **tab_env)
{
	char	*key;
	char	*value;
	int		x;

	x = 0;
	value = NULL;
	while ((*str)[i + x] && ft_isspace((*str)[i + x]) == 0 && x < 80)
		x += 1;
	key = ft_strsub(*str, i, x);
	if (x >= 80)
	{
		write(2, "21sh: env: error too long arguments\n", 31);
		free(key);
		return (-1);
	}
	else
	{
		value = get_env_value(tab_env, key);
		ft_delete_inside(str, i, x);
		ft_printf("str after delete: |%s|\n", *str);
		replace_str(str, value, i);
	}
	free(key);
	return (0);
}

void		remove_quote(char **s, int *i, char **tab_env)
{
	char	*sub;
	char	*str;
	char	quote;
	int		save;
	int		x;

	x = -1;
	sub = NULL;
	str = NULL;
	quote = (*s)[(*i)++];
	save = *i;
	while ((*s)[*i] && (*s)[*i] != quote)
		*i += 1;
	sub = (quote == '\'') ? ft_strsub(*s, save, *i - save) : 0;
	if (quote == '"')
	{
		sub = ft_strsub(*s, save, *i - save);
		while (sub[x++])
			(sub[x] == '$') ? replace_env_var(&sub, x, tab_env) : 0;
	}
	else if (quote == '`')
	{
		sub = ft_strsub(*s, save, *i - save);
	}
	(sub != NULL) ? ft_insert(s, sub, save - 1) : 0;
}

void		convert_quote(char **s, char **tab_env)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '$')
		{
			if (replace_env_var(s, i, tab_env) == -1)
				return ;
		}
		else if (ft_isquote((*s)[i]) == 1)
		{
			remove_quote(s, &i, tab_env);
			i -= 2;
		}
		else
			i += 1;
	}
}
