/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:50:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/26 18:03:27 by tcollard         ###   ########.fr       */
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

//	void	lettre_operator(char const *s, int *i, int *nb_lettre)
//	{
//		int save;
//		int	start;
//		save = 0;
//		start = *i;
//		if (*nb_lettre == 0)
//		{
//			while (s[*i] && ft_isdigit(s[*i]) == 1)
//				*i += 1;
//			while (s[*i] == '<' || s[*i] == '>' || s[*i] == '|' || s[*i] == '&')
//				*i += 1;
//			save = *i;
//			while (ft_isdigit(s[*i]) == 1)
//				*i += 1;
//			if (s[*i] && ft_isspace(s[*i]) == 0)
//				*i = save;
//			*nb_lettre = *i - start;
//		}
//	}

void	digit_number(char *s, int i, int add, int *nb_lettre)
{
	while (s[i] && ft_isdigit(s[i]) == 1)
	{
		i += 1;
		*nb_lettre += 1;
	}
	while (s[i + add] && ft_isspace(s[i + add]) == 0 && s[i + add] != '<' &&
	s[i + add] != '>' && s[i + add] != '|' && s[i + add] != '&')
		add += 1;
	if (add != 0)
		*nb_lettre += add;
	else
	{
		while (s[i] && (s[i] == '<' || s[i] == '>' || s[i] == '|' ||
		s[i] == '&'))
		{
			i += 1;
			*nb_lettre += 1;
		}
		while (s[i + add] && ft_isdigit(s[i + add]) == 1)
			add += 1;
		if (!s[i + add] || ft_isspace(s[i + add]) == 1)
			*nb_lettre += add;
	}
}

int		check_operator(char *s, int *i, unsigned int *nb_word)
{
	int	x;

	x = 1;
	while (*i - x >= 0 && ft_isspace(s[*i - x]) == 0 &&
	ft_isdigit(s[*i - x]) == 1)
		x += 1;
	*nb_word += (*i - x >= 0 && ft_isspace(s[*i - x]) == 0) ? 1 : 0;
	x = 1;
	while (s[*i + x] && (s[*i + x] == '<' || s[*i + x] == '>' ||
	s[*i + x] == '&' || s[*i + x] == '|'))
		x += 1;
	while (s[*i + x] && ft_isdigit(s[*i + x]))
		x += 1;
	*i += x;
	*nb_word += (s[*i] && ft_isspace(s[*i]) == 0) ? 1 : 0;
	return (0);
}

int		position_operator(char const *s, int *i, int wn, int *iw)
{
	int	x;
	int pos;

	x = 1;
	pos = 0;
	while (*i - x >= 0 && ft_isspace(s[*i - x]) == 0 &&
	ft_isdigit(s[*i - x]) == 1)
		x += 1;
	pos = (*i - x < 0 || ft_isspace(s[*i - x]) == 1) ? *i - x + 1 : *i;
	*iw += (*i - x < 0 || ft_isspace(s[*i - x]) == 1) ? 0 : 1;
	if (*iw == wn)
		return (pos);
	while (s[*i] && (s[*i] == '<' || s[*i] == '>' || s[*i] == '&'
	|| s[*i] == '|'))
		*i += 1;
	x = 0;
	while (s[*i + x] && ft_isdigit(s[*i + x]) == 1)
		x += 1;
	if (s[*i + x] && ft_isspace(s[*i + x]) == 0)
		*iw += 1;
	else
		*i += x;
	return (*i);
}
