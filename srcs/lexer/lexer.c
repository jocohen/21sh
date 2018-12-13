/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:01 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/13 18:48:41 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	read_lexer(char **lexer, t_env **lst_env, t_ast *lst,
	t_alloc **alloc)
{
	int	i;
	int	x;

	i = 0;
	while (lexer && lexer[i])
	{
		x = 0;
		while (lexer[i][x] && ft_isspace(lexer[i][x]))
			x += 1;
		(lexer[i][x]) ? clean_input(lexer[i], lst, lst_env, alloc) : 0;
		free(lexer[i]);
		i += 1;
	}
	(lexer != NULL) ? free(lexer) : 0;
}

void		lexer(char *input, t_env **lst_env, t_alloc *alloc)
{
	int		i;
	char	**lexer;
	t_ast	*lst;

	i = 0;
	lexer = NULL;
	lst = NULL;
	check_opening_quote(&input, alloc);
	check_cmd_pipe(&input, alloc, 0);
	while (input[i] == ';')
		i += 1;
	if ((lexer = ft_strsplit_shell(&input[i], ';')) == NULL)
		return ;
		ft_printf("READ LEXER\n");
	read_lexer(lexer, lst_env, lst, &alloc);
}

void		clean_input(char *str, t_ast *lst, t_env **lst_env,
	t_alloc **alloc)
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
	parser(split, lst, lst_env, alloc);
}
