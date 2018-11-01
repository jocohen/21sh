/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:50:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/01 19:36:59 by tcollard         ###   ########.fr       */
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

void	nb_lettre_operator(char *s, int i, int *nb_lettre)
{
	int	x;
	int	add;

	x = 0;
	add = 0;
	if (type_operator(s, &i) == 1)
	{
		if (*nb_lettre == 0)
			while (s[i + *nb_lettre] && ft_isoperator(s[i + *nb_lettre]) == 1)
				*nb_lettre += 1;
		return ;
	}
	while (s[i + x] && ft_isoperator(s[i + x]) == 1)
		x += 1;
	*nb_lettre += x;
	i += x;
	x = (s[i] == '-' && s[i - 1] == '&' && ft_isspace(s[i + 1]) == 1) ? 1 : 0;
	while (s[i + add] && ft_isdigit(s[i + add]) == 1)
		add += 1;
	*nb_lettre += (!s[i + add] || ft_isspace(s[i + add]) == 0) ? 0 : add;
	*nb_lettre += x;
}

int		check_redir(char *s, int *i, unsigned int *nb_word)
{
	int	x;

	x = 0;
	while (ft_isoperator(s[*i + x]) == 1)
		x += 1;
	if (s[*i + x] == '-' && s[*i + x - 1] == '&' &&
	ft_isspace(s[*i + x + 1]) == 1)
		x += 1;
	if (x > 3)
	{
		ft_printf("ERROR: len = %d\n", x);
		return (-1);
	}
	else if (check_operator(s, i, nb_word, x) == 1)
	{
		*i += x;
		return (0);
	}
	return (-1);
}

int		position_redir(char const *s, int *i, int wn, int *iw)
{
	int	x;

	x = 1;
	if (type_operator(s, i) == 1)
	{
		if (*i > 0 && ft_isspace(s[*i - 1]) == 0 && (*iw += 1) == wn)
			return (*i);
		while (s[*i] && ft_isoperator(s[*i]) == 1)
			*i += 1;
		if (ft_isspace(s[*i]) == 0 && (*iw += 1) == wn)
			return (*i);
	}
	else
	{
		while (*i - x >= 0 && ft_isdigit(s[*i - x]) == 1)
			x += 1;
		if ((*iw += (*i - x < 0 || ft_isspace(s[*i - x]) == 1) ? 0 : 1) == wn)
			return (*i);
		while (s[*i] && ft_isoperator(s[*i]) == 1)
			*i += 1;
		get_position(s, i, wn, iw);
	}
	return (*i);
}
