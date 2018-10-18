/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 11:52:14 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/02 11:52:15 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
**	int	ft_error_parse(char *s, int count)
**	{
**		int	error;
**
**		error = 0;
**		if (s[0] == '<')
**		{
**			if (count <= 3)
**				error = ft_printf("21sh: parse error near `\\n'\n");
**			else if (count == 4)
**				error = ft_printf("21sh: parse error near `<'\n");
**			else if (count == 5)
**				error = ft_printf("21sh: parse error near `<<'\n");
**			else if (count >= 6)
**				error = ft_printf("21sh: parse error near `<<<'\n");
**		}
**		else if (s[0] == '>')
**		{
**			if (count < 3)
**				error = ft_printf("21sh: parse error near `\\n'\n");
**			else if (count == 3)
**				error = ft_printf("21sh: parse error near `>'\n");
**			else if (count == 4)
**				error = ft_printf("21sh: parse error near `>>'\n");
**		}
**		if (error != 0)
**			return (-1);
**		return (0);
**	}
*/

int	ft_error(char *s, int error)
{
	if (error == 0)
		ft_printf("21sh: parse error near `%s'\n", s);
	else if (error == 1)
		ft_printf("21sh: parse error near `%c'\n", s[0]);
	else if (error == 2)
		ft_printf("21sh: parse error near `%c%c'\n", s[0], s[1]);
	else
		ft_printf("21sh: parse error near `\\n'\n");
	return (-1);
}
