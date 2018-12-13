/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:51:28 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/15 17:51:30 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	prompt_pipe(char **input)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	write(1, "pipe > ", 7);
	get_next_line(0, &s);
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	check_opening_quote(input);
}

static void	prompt_cmdor(char **input)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	write(1, "cmdor > ", 8);
	get_next_line(0, &s);
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	check_opening_quote(input);
}

static void	prompt_cmdand(char **input)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	write(1, "cmdand > ", 9);
	get_next_line(0, &s);
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	check_opening_quote(input);
}

static int	check_next_empty(char **input, int i)
{
	while ((*input)[i] && ft_isspace((*input)[i]) == 1)
		i += 1;
	if ((*input)[i] == '\0')
		return (1);
	return (0);
}

void		check_cmd_pipe(char **input)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '|' || (*input)[i] == '&')
		{
			while (j < i && ft_isspace((*input)[j]) == 1)
				j += 1;
			if (i == j)
				return ;
		}
		if ((*input)[i] == '|' && (*input)[i + 1] != '|')
			(check_next_empty(input, i + 1) == 1) ? prompt_pipe(input) : 0;
		else if ((*input)[i] == '|' && (*input)[i + 1] == '|')
			(check_next_empty(input, i + 2) == 1) ? prompt_cmdor(input) : 0;
		else if ((*input)[i] == '&' && (*input)[i + 1] == '&')
			(check_next_empty(input, i + 2) == 1) ? prompt_cmdand(input) : 0;
		i += 1;
	}
}
