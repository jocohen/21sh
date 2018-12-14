/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:57 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/14 12:01:03 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_isquote(char c)
{
	if (c == '\'' || c == '"' || c == '`')
		return (1);
	return (0);
}

int		ft_isoperator(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	ft_insert(char **source, char *insert, int pos1, int pos2)
{
	char	*begin;
	char	*end;
	char	*tmp;

	begin = ft_strsub(*source, 0, pos1);
	end = ft_strsub(*source, pos2 + 1, (ft_strlen(&((*source)[pos2]) - 1)));
	free(*source);
	tmp = ft_strjoin(begin, insert);
	*source = ft_strjoin(tmp, end);
	free(begin);
	free(tmp);
	free(end);
	free(insert);
}

void	ft_delete_inside(char **source, int start, int len)
{
	char	*begin;
	char	*end;

	begin = ft_strsub(*source, 0, start);
	end = ft_strsub(*source, start + len, ft_strlen(&(*source)[len + start]));
	free(*source);
	*source = ft_strjoin(begin, end);
	free(begin);
	free(end);
}

int		ft_str_is_empty(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (ft_isspace(s[i]) == 0)
			return (0);
		i += 1;
	}
	return (1);
}
