/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:50:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/30 19:12:38 by tcollard         ###   ########.fr       */
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

	ft_printf("In tha quote counter\n");
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

void	digit_number(char *s, int i, int add, int *nb_lettre)
{
	while (s[i + *nb_lettre] && ft_isdigit(s[i + *nb_lettre]) == 1)
		*nb_lettre += 1;
	i += *nb_lettre;
	while (s[i + add] && ft_isspace(s[i + add]) == 0 &&
	ft_isoperator(s[i + add]) == 0)
		add += 1;
	if (add != 0)
		*nb_lettre += add;
	else
	{
		while (s[i] && ft_isoperator(s[i]) == 1)
		{
			i += 1;
			*nb_lettre += 1;
		}
		if (s[i] == '-' && ft_isspace(s[i + 1]) == 1)
			*nb_lettre += 1;
		else
		{
			while (s[i + add] && ft_isdigit(s[i + add]) == 1)
				add += 1;
			if (!s[i + add] || ft_isspace(s[i + add]) == 1)
				*nb_lettre += add;
		}
	}
}

void	check_redir(char *s, int *i, unsigned int *nb_word)
{
	int		x;

	x = 1;
	if (check_operator(s, i, nb_word) == 1)
		return ;
	while (*i - x >= 0 && ft_isdigit(s[*i - x]) == 1)
		x += 1;
	*nb_word += (*i - x >= 0 && ft_isspace(s[*i - x]) == 0) ? 1 : 0;
	x = 1;
	while (s[*i + x] && ft_isoperator(s[*i + x]) == 1)
		x += 1;
	if (s[*i + x] == '-' && ft_isspace(s[*i + x + 1]) == 1)
		*i += x + 1;
	else
	{
		while (s[*i + x] && ft_isdigit(s[*i + x]))
			x += 1;
		*i += x;
	}
	*nb_word += (s[*i] && ft_isspace(s[*i]) == 0) ? 1 : 0;
}

int		position_redir(char const *s, int *i, int wn, int *iw)
{
	int	x;
	int pos;

	x = 1;
	pos = 0;
	position_operator(s, i, wn, iw);
	if (*iw == wn)
		return (*i);
	while (*i - x >= 0 && ft_isdigit(s[*i - x]) == 1)
		x += 1;
	pos = (*i - x < 0 || ft_isspace(s[*i - x]) == 1) ? *i - x + 1 : *i;
	if ((*iw += (*i - x < 0 || ft_isspace(s[*i - x]) == 1) ? 0 : 1) == wn)
		return (pos);
	while (s[*i] && ft_isoperator(s[*i]) == 1)
		*i += 1;
	(s[*i] == '-' && ft_isspace(s[*i + 1]) == 1) ? *i += 2 : 0;
	(s[*i] == '-' && ft_isspace(s[*i + 1]) == 1) ? *iw += 1 : 0;
	if (s[*i] != '-' || ft_isspace(s[*i + 1]) == 0)
	{
		x = 0;
		while (s[*i + x] && ft_isdigit(s[*i + x]) == 1)
			x += 1;
		if (s[*i + x] && ft_isspace(s[*i + x]) == 0)
			*iw += 1;
		else
			*i += x;
	}
	return (*i);
}
