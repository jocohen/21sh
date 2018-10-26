/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:50:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/26 17:42:28 by tcollard         ###   ########.fr       */
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
	int save;
	int	start;

	save = 0;
	start = *i;
	// ft_printf("Lettre opeartor-> s: |%s|\nnb_lettre = %d\nstart pos = %d i = %d", &s[*i], *nb_lettre, start, *i);
	if (*nb_lettre == 0)
	{
		// ft_printf("\nenter search\n");
		while (s[*i] && ft_isdigit(s[*i]) == 1)
			*i += 1;
		// ft_printf("postion start digit s: |%s|\n", &s[*i]);
		while (s[*i] == '<' || s[*i] == '>' || s[*i] == '|' || s[*i] == '&')
			*i += 1;
		save = *i;
		// ft_printf("postion after op sign s: |%s|\n", &s[*i]);
		while (ft_isdigit(s[*i]) == 1)
			*i += 1;
		// ft_printf("postion end digit s: |%s|\n", &s[*i]);
		if (s[*i] && ft_isspace(s[*i]) == 0)
			*i = save;
		// ft_printf("final i = %d position = |%s| nb = %d\n", *i, &s[*i], *i - start);
		*nb_lettre = *i - start;
	}
}

/*
**	OLD VERSION OF LETTRE OPERATOR
**	void	lettre_operator(char const *s, int *i, int *nb_lettre)
**	{
**		char	c;
**
**		ft_printf("Lettre opeartor-> s: |%s|\n", &s[*i]);
**		if (*nb_lettre == 0)
**		{
**			c = s[*i];
**			while (s[*i] == c)
**			{
**				*i += 1;
**				*nb_lettre += 1;
**			}
**			(s[*i] == '&') ? c = s[*i] : 0;
**			while (s[*i] == c)
**			{
**				*i += 1;
**				*nb_lettre += 1;
**			}
**		}
**	}
*/

/*
** STEP:
** 1 - Check if before is space or digit
** 2 - if digit check before if is ft_isspace
** 3 - if it is start oprator on this index
** 4 - while it is < > & | continu
** 5 - if it space quite function
** 6 - if it digit continu until space
** 7 - if lettre after digit, operator ending on last < > & |
** * - return ;
*/

int			check_operator(char *s, int *i, unsigned int *nb_word)
{
	int	x;

	x = 1;
	// ft_printf("INIT nb word = %d\ns: |%s|\n\n", *nb_word, &s[*i]);
	while (*i - x >= 0 && ft_isspace(s[*i - x]) == 0 &&
	ft_isdigit(s[*i - x]) == 1)
		x += 1;
	*nb_word += (*i - x >= 0 && ft_isspace(s[*i - x]) == 0) ? 1 : 0;
	x = 1;
	// ft_printf("1 => nb word = %d\ns: |%s|\n\n", *nb_word, &s[*i]);
	while (s[*i + x] && (s[*i + x] == '<' || s[*i + x] == '>' ||
	s[*i + x] == '&' || s[*i + x] == '|'))
		x += 1;
	while (s[*i + x] && ft_isdigit(s[*i + x]))
		x += 1;
	*i += x;
	*nb_word += (s[*i] && ft_isspace(s[*i]) == 0) ? 1 : 0;
	return (0);
}

/*
**	SAVE OLD VERSION OF CHECK OPERATOR
** int		check_operator(char *s, int *i, unsigned int *nb_word)
** {
** 	char	c;
** 	int		count;
**
** 	count = 1;
** 	(*i - 1 >= 0 && ft_isspace(s[*i - 1]) == 0 && s[*i - 1] != '<' &&
** 	s[*i - 1] != '>' && s[*i - 1] != '|' && s[*i - 1] != '&')
** 	? *nb_word += 1 : 0;
** 	c = s[(*i)++];
** 	while (s[*i] && s[*i] == c)
** 	{
** 		*i += 1;
** 		count += 1;
** 	}
** 	(s[*i] == '&') ? c = s[*i] : 0;
** 	while (s[*i] == c)
** 	{
** 		*i += 1;
** 		count += 1;
** 	}
** 	(s[*i] && ft_isspace(s[*i]) == 0) ? *nb_word += 1 : 0;
** 	return (0);
** }
*/

int			position_operator(char const *s, int *i, int wn, int *iw)
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

/*
**	OLD VERSION OF POSITION OPERATOR
**	int		position_operator(char const *s, int *i, int wn, int *iw)
**	{
**		char	c;
**
**		(*i - 1 >= 0 && ft_isspace(s[*i - 1]) == 0 && s[*i - 1] != '<' &&
**		s[*i - 1] != '>' && s[*i - 1] != '|' && s[*i - 1] != '&') ? *iw += 1 : 0;
**		if (*iw == wn)
**			return (*i);
**		c = s[(*i)++];
**		while (s[*i] && s[*i] == c)
**			*i += 1;
**		(s[*i] && ft_isspace(s[*i]) == 0 && s[*i] != '&') ? *iw += 1 : 0;
**		return (*i);
**	}
*/
