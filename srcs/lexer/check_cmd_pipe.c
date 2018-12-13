/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:51:28 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/13 19:00:09 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	prompt_pipe(char **input, t_alloc *alloc, int del)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	s = recall_prompt(alloc, 5, del);
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	check_opening_quote(input, alloc);
}

static void	prompt_cmdor(char **input, t_alloc *alloc, int del)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	s = recall_prompt(alloc, 7, del);
	// ft_printf("s = |%s|\n", s);
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	// ft_printf("INPUT: |%s|\n", *input);
	check_opening_quote(input, alloc);
}

static void	prompt_cmdand(char **input, t_alloc *alloc, int del)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	s = recall_prompt(alloc, 6, del);
	tmp = ft_strjoin(*input, " ");
	free(*input);
	*input = ft_strjoin(tmp, s);
	free(tmp);
	check_opening_quote(input, alloc);
}

static int	check_next_empty(char **input, int i)
{
	while ((*input)[i] && ft_isspace((*input)[i]) == 1)
		i += 1;
	if ((*input)[i] == '\0')
		return (1);
	return (0);
}

void		check_cmd_pipe(char **input, t_alloc *alloc, int del)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*input)[i])
	{
		// ft_printf("INPUT[%d]: |%c|\n", i, (*input)[i]);
		if ((*input)[i] == '|' || (*input)[i] == '&')
		{
			while (j < i && ft_isspace((*input)[j]) == 1)
				j += 1;
			if (i == j)
				return ;
		}
		if ((*input)[i] == '|' && (*input)[i + 1] != '|' && (*input)[i - 1] != '|')
			(check_next_empty(input, i + 1) == 1) ? prompt_pipe(input, alloc,
																del++) : 0;
		else if ((*input)[i] == '|' && (*input)[i + 1] == '|')
			(check_next_empty(input, i + 2) == 1) ? prompt_cmdor(input, alloc,
																	del++) : 0;
		else if ((*input)[i] == '&' && (*input)[i + 1] == '&')
			(check_next_empty(input, i + 2) == 1) ? prompt_cmdand(input,
															alloc, del++) : 0;
		i += 1;
	}
}
