/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespace_shell.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:25:49 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/30 15:58:00 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static int	ft_word_counter(char *s, unsigned int *nb_word)
{
	int	i;

	i = 0;
	while (s[i])
	{
		(ft_isspace(s[i]) == 0) ? *nb_word += 1 : 0;
		while (s[i] && ft_isspace(s[i]) == 0)
		{
			if (ft_isquote(s[i]) == 1)
				in_quote(s, &i);
			else if (ft_isoperator(s[i]) == 1)
				check_operator(s, &i, nb_word);
			else
				i += 1;
		}
		(s[i]) ? i += 1 : 0;
	}
	return (0);
}

static void	ft_position_word(char *s, int wn, int *pos)
{
	int	i;
	int	wd_search;

	i = 0;
	wd_search = -1;
	while (s[i])
	{
		*pos = (ft_isspace(s[i]) == 0 && (wd_search += 1) == wn) ? i : 0;
		if (wn == wd_search)
			return ;
		while (s[i] && ft_isspace(s[i]) == 0)
		{
			if (ft_isquote(s[i]) == 1)
				in_quote(s, &i);
			else if (ft_isoperator(s[i]) == 1)
			{
				*pos = position_operator(s, &i, wn, &wd_search);
				if (wn == wd_search)
					return ;
			}
			else
				i += 1;
		}
		(s[i]) ? i += 1 : 0;
	}
}

static void	ft_counter_lettre(char *s, unsigned int word_n, int *nl)
{
	int i;
	int	add;

	i = 0;
	add = 0;
	ft_position_word(s, word_n, &i);
	(ft_isdigit(s[i]) == 1) ? digit_number(s, i, add, nl) : 0;
	if (ft_isoperator(s[i]) == 1 && *nl == 0)
	{
		while (s[i + *nl] && ft_isoperator(s[i + *nl]) == 1)
			*nl += 1;
		(s[i + *nl] == '-' && ft_isspace(s[i + *nl + 1]) == 1) ? *nl += 1 : 0;
		if (s[i + *nl] != '-' || ft_isspace(s[i + *nl + 1]) == 0)
			while (s[i + add + *nl] && ft_isdigit(s[i + add + *nl]) == 1)
				add += 1;
		*nl += (!s[i + add + *nl] || ft_isspace(s[i + add + *nl]) == 1) ?
		add : 0;
	}
	else if (*nl == 0)
		while (s[i] && ft_isoperator(s[i]) == 0 && ft_isspace(s[i]) == 0)
		{
			(ft_isquote(s[i]) == 1) ? lettre_in_quote(s, &i, nl) : 0;
			i += 1;
			*nl += 1;
		}
}

static void	ft_fill(char *s, unsigned int wrd_n, char **split, int max_lettre)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_position_word(s, wrd_n, &i);
	while (j < max_lettre)
		split[wrd_n][j++] = s[i++];
	split[wrd_n][j] = '\0';
}

char		**ft_splitwhitespace_shell(char *s)
{
	unsigned int	nb_word;
	unsigned int	i;
	char			**split;
	int				nb_lettre;

	i = 0;
	nb_word = 0;
	if (!s)
		return (NULL);
	if (ft_word_counter(s, &nb_word) == -1)
		return (NULL);
	if (!(split = (char**)malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	while (i < nb_word)
	{
		nb_lettre = 0;
		ft_counter_lettre((char*)s, i, &nb_lettre);
		ft_printf("word %d nb lettre = %d\n", i, nb_lettre);
		if (!(split[i] = (char*)malloc(sizeof(char) * (nb_lettre + 1))))
			return (NULL);
		ft_fill((char *)s, i, split, nb_lettre);
		i += 1;
	}
	split[nb_word] = 0;
	return (split);
}
