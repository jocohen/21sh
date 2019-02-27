/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:00:27 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/27 15:22:39 by jonascohen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	*missing_quote_prompt(char c, t_alloc *al)
{
	char	*s;
	char	*input;

	s = NULL;
	input = NULL;
	while (c != '\0')
	{
		if (c == '\'')
			s = recall_prompt(al, 3);
		else if (c == '"')
			s = recall_prompt(al, 2);
		else if (c == '`')
			s = recall_prompt(al, 4);
		if (!s)
		{
			ft_memdel((void **)&input);
			return (0);
		}
		check_closing_quote(&c, s, &input, al);
		ft_memdel((void **)&s);
	}
	return (input);
}

void	init_ast(char **input, char *s)
{
	char	*tmp;

	if (*input == NULL)
	{
		if (!(*input = ft_strjoin("\n", s)))
			ft_exit_malloc();
	}
	else
	{
		if (!(tmp = ft_strjoin(*input, "\n")))
			ft_exit_malloc();
		ft_memdel((void **)input);
		if (!(*input = ft_strjoin(tmp, s)))
			ft_exit_malloc();
		ft_memdel((void **)&tmp);
	}
}

void	check_closing_quote(char *c, char *s, char **input, t_alloc *alloc)
{
	int	i;

	if (*input)
		i = ft_strlen(*input);
	else
		i = 0;
	init_ast(input, s);
	while ((*input)[i] && (*input)[i] != *c)
		i += 1;
	if ((*input)[i] == '\0')
		return ;
	else if ((*input)[i] == *c)
	{
		*c = '\0';
		i += 1;
		while ((*input)[i])
		{
			if (ft_isquote((*input)[i]) == 1)
				find_closing(input, &i, alloc);
			i += 1;
		}
	}
}
