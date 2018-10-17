/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:50:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/01 12:00:47 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	in_quote(char const *s, int *i)
{
	char	quote;

	quote = s[*i];
	*i += 1;
	while (s[*i] && s[*i] != quote)
		*i += 1;
	*i += 1;
}

void	lettre_in_quote(char const *s, int *i, int *nb_lettre)
{
	char	quote;

	quote = s[*i];
	*i += 1;
	*nb_lettre += 1;
	while (s[*i] && s[*i] != quote)
	{
		*i += 1;
		*nb_lettre += 1;
	}
	*i += 1;
	*nb_lettre += 1;
}

void	lettre_operator(char const *s, int *i, int *nb_lettre)
{
	char	c;

	if (*nb_lettre == 0)
	{
		c = s[*i];
		while (s[*i] == c)
		{
			*i += 1;
			*nb_lettre += 1;
		}
		(s[*i] == '&') ? c = s[*i] : 0;
		while (s[*i] == c)
		{
			*i += 1;
			*nb_lettre += 1;
		}
	}
}

int		check_operator(char *s, int *i, unsigned int *nb_word)
{
	char	c;
	int		count;

	count = 1;
	(*i - 1 >= 0 && ft_isspace(s[*i - 1]) == 0 && s[*i - 1] != '<' &&
	s[*i - 1] != '>' && s[*i - 1] != '|' && s[*i - 1] != '&')
	? *nb_word += 1 : 0;
	c = s[(*i)++];
	while (s[*i] && s[*i] == c)
	{
		*i += 1;
		count += 1;
	}
	(s[*i] == '&') ? c = s[*i] : 0;
	while (s[*i] == c)
	{
		*i += 1;
		count += 1;
	}
	(s[*i] && ft_isspace(s[*i]) == 0) ? *nb_word += 1 : 0;
	return (0);
}

int		position_operator(char const *s, int *i, int wn, int *iw)
{
	char	c;

	(*i - 1 >= 0 && ft_isspace(s[*i - 1]) == 0 && s[*i - 1] != '<' &&
	s[*i - 1] != '>' && s[*i - 1] != '|' && s[*i - 1] != '&') ? *iw += 1 : 0;
	if (*iw == wn)
		return (*i);
	c = s[(*i)++];
	while (s[*i] && s[*i] == c)
		*i += 1;
	(s[*i] && ft_isspace(s[*i]) == 0 && s[*i] != '&') ? *iw += 1 : 0;
	return (*i);
}
