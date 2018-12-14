/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:51:28 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/14 14:49:52 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	prompt_pipe(char **input, t_alloc *alloc)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	while (!s || ft_str_is_empty(s) == 1)
	{
		ft_memdel((void **)&s);
		s = recall_prompt(alloc, 5);
	}
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	ft_memdel((void **)&s);
	check_opening_quote(input, alloc);
	check_cmd_pipe(input, alloc);
}

static void	prompt_cmdor(char **input, t_alloc *alloc)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	while (!s || ft_str_is_empty(s) == 1)
	{
		ft_memdel((void **)&s);
		s = recall_prompt(alloc, 7);
	}
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	ft_memdel((void **)&s);
	check_opening_quote(input, alloc);
	check_cmd_pipe(input, alloc);
}

static void	prompt_cmdand(char **input, t_alloc *alloc)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	while (!s || ft_str_is_empty(s) == 1)
	{
		ft_memdel((void **)&s);
		s = recall_prompt(alloc, 6);
	}
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	ft_memdel((void **)&s);
	check_opening_quote(input, alloc);
	check_cmd_pipe(input, alloc);
}

static int	check_next_empty(char **input, int *i, int add)
{
	int	x;

	x = 0;
	*i += add;
	while ((*input)[*i + x] && ft_isspace((*input)[*i + x]) == 1)
		x += 1;
	if ((*input)[*i] == '\0')
		return (1);
	return (0);
}

void		check_cmd_pipe(char **input, t_alloc *alloc)
{
	int	i;
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
			(check_next_empty(input, &i, 1) == 1) ? prompt_pipe(input, alloc) : 0;
		else if ((*input)[i] == '|' && (*input)[i + 1] == '|')
			(check_next_empty(input, &i, 2) == 1) ? prompt_cmdor(input, alloc) : 0;
		else if ((*input)[i] == '&' && (*input)[i + 1] == '&')
			(check_next_empty(input, &i, 2) == 1) ? prompt_cmdand(input, alloc) : 0;
		i += 1;
	}
}
