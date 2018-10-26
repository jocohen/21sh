/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:57 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/26 18:10:34 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

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

void	ft_insert(char **source, char *insert, int pos)
{
	char	*begin;
	char	*end;
	char	*tmp;

	begin = ft_strsub(*source, 0, pos);
	end = ft_strsub(*source, pos + ft_strlen(insert) + 2, ft_strlen(*source));
	free(*source);
	tmp = ft_strjoin(begin, insert);
	*source = ft_strjoin(tmp, end);
	free(begin);
	free(tmp);
	free(end);
}
