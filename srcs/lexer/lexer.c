/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:01 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/27 16:15:06 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	lexer(char *input, t_env *lst_env)
{
	int		i;
	int		x;
	char	**lexer;
	t_ast	*lst;

	i = 0;
	lexer = NULL;
	lst = NULL;
	check_opening_quote(&input);
	check_cmd_pipe(&input);
	while (input[i] == ';')
		i += 1;
	if ((lexer = ft_strsplit_shell(&input[i], ';')) == NULL)
	{
		free(input);
		return ;
	}
	i = 0;
	while (lexer && lexer[i])
	{
		x = 0;
		while (lexer[i][x] && ft_isspace(lexer[i][x]))
			x += 1;
		if (lexer[i][x])
			clean_input(lexer[i], lst, lst_env);
		free(lexer[i]);
		i += 1;
	}
	(lexer != NULL) ? free(lexer) : 0;
	free(input);
}

void	clean_input(char *str, t_ast *lst, t_env *lst_env)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	if ((split = ft_splitwhitespace_shell(str)) == NULL)
		return ;
	while (split[i])
	{
		if (convert_quote(&(split[i]), lst_env) == -1)
			return ;
		i += 1;
	}
	parser(split, lst, lst_env);
}
