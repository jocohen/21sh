/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:07 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/05 18:44:24 by tcollard         ###   ########.fr       */
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
		ft_printf("else\n");
		begin = ft_strsub(*str, 0, pos);
		ft_printf("After begin: |%s|\n", begin);
		end = ft_strsub(*str, pos, ft_strlen(*str));
		ft_printf("After end: %s\n", end);
		free(*str);
		tmp = ft_strjoin(begin, insert);
		ft_printf("TMP: %s\n", tmp);
		*str = ft_strjoin(tmp, end);
		ft_printf("STR: %s\n", *str);
		free(tmp);
		free(begin);
		free(end);
	}
}

static void	replace_env_var(char **str, int i, char **tab_env)
{
	char	*key;
	char	*value;
	int		x;

	x = 0;
	value = NULL;
	ft_printf("Before loop\n");
	while ((*str)[i + x] && ft_isspace((*str)[i + x]) == 0 && x < 10)
		x += 1;
	key = ft_strsub(*str, i, x);
	ft_printf("key = |%s|\n", key);
	if (x >= 10)
		ft_printf("21sh: error too long arguments\n");
	else
	{
		value = get_env_value(tab_env, key);
		ft_printf("===> Value = |%s|\n", value);
		// if (i > 0)
			ft_delete_inside(str, i, x);
		ft_printf("str = |%s|\n", *str);
		// ft_insert(str, value, i);
		replace_str(str, value, i);
		ft_printf("AFTER INSERT: |%s|\n", *str);
	}
	free(key);
}

void	remove_quote(char **s, int *i, char **tab_env)
{
	char	*sub;
	char	*str;
	char	quote;
	int		save;

	sub = NULL;
	str = NULL;
	(void)tab_env;
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

void	convert_quote(char **s, char **tab_env)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{
		if (*s[i] == '$')
		{
			ft_printf("GO TO REPLACE IT: |%s|\n", &(*s[i]));
			replace_env_var(s, i, tab_env);
		}
		ft_printf("NEXT: %d\n", i);	
		if (ft_isquote((*s)[i]) == 1)
		{
			remove_quote(s, &i, tab_env);
			i -= 2;
		}
		else
			i += 1;
	}
}
