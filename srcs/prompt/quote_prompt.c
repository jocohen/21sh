/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:00:27 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/02 15:00:29 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

char	*missing_quote_prompt(char c)
{
	int		r;
	char	*s;
	char	*input;

	r = 1;
	s = NULL;
	input = NULL;
	while (r > 0 && c != '\0')
	{
		if (c == '\'')
			write(1, "quote > ", 8);
		else if (c == '"')
			write(1, "dquote > ", 9);
		else if (c == '`')
			write(1, "bquote > ", 9);
		r = get_next_line(0, &s);
		check_closing_quote(&c, s, &input);
		free(s);
	}
	return (input);
}

void	init_ast(char **input, char *s)
{
	char	*tmp;

	if (*input == NULL)
		*input = ft_strjoin("\n", s);
	else
	{
		tmp = ft_strjoin(*input, "\n");
		free(*input);
		*input = ft_strjoin(tmp, s);
		free(tmp);
	}
}

void	check_closing_quote(char *c, char *s, char **input)
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
				find_closing(input, &i);
			i += 1;
		}
	}
}
