/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:01 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/01 11:29:57 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
**	ADD TERMCAPS OF JO TO ADD NEW INPUT
*/

void	lexer(char *input)
{
	int		i;
	char	**lexer;
	t_ast	*lst;

	i = 0;
	lexer = NULL;
	lst = NULL;
	check_opening_quote(&input);
	check_cmd_pipe(&input);
	if ((lexer = ft_strsplit_shell(input, ';')) == NULL)
	{
		free(input);
		return ;
	}
	while (lexer && lexer[i])
	{
		ft_printf("lexer[%d]: %s\n", i, lexer[i]);
		clean_input(lexer[i], lst);
		free(lexer[i]);
		i += 1;
	}
	(lexer != NULL) ? free(lexer) : 0;
	free(input);
}

void	clean_input(char *str, t_ast *lst)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	if ((split = ft_splitwhitespace_shell(str)) == NULL)
		return ;
	while (split[i])
	{
		convert_quote(&(split[i]));
		if ((split[i][0] == '<' || split[i][0] == '>') && !split[i + 1])
		{
			(ft_strlen(split[i]) > 2) ? ft_error(split[i], 2) : ft_error(0, 10);
			return ;
		}
		else if (i == 0 && (split[i][0] == '|' || split[i][0] == '&'))
		{
			ft_error(split[i], 2);
			return ;
		}
		i += 1;
	}
	parser(split, lst);
}
