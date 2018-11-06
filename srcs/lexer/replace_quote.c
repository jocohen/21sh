/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:07 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/06 18:58:36 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
 ** In back quote
 ** execute commande
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

	x = 1;
	value = NULL;
	while ((*str)[i + x] && x < 80 && ft_isalnum((*str)[i + x]) == 1)
		x += 1;
	if (x >= 80)
	{
		write(2, "21sh: env: error too long arguments\n", 31);
		return (-1);
	}
	else
	{
		key = ft_strsub(*str, i, x);
		value = get_env_value(tab_env, key);
		ft_delete_inside(str, i, x);
		(value[0] != '\0') ? replace_str(str, value, i) : 0;
		free(key);
	}
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
	(sub != NULL) ? ft_insert(s, sub, save - 1, *i) : 0;
}

void		convert_quote(char **s, char **tab_env)
{
	int		i;

	i = 0;
	if (ft_strcmp(*s, "~") == 0)
	{
		free(*s);
		*s = ft_strdup(get_env_value(tab_env, "$HOME"));
		return ;
	}
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
