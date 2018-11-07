/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:26:01 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 17:10:18 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	lexer(char *input, t_env **lst_env)
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
		clean_input(lexer[i], lst, lst_env);
		free(lexer[i]);
		i += 1;
	}
	(lexer != NULL) ? free(lexer) : 0;
	free(input);
}

void	clean_input(char *str, t_ast *lst, t_env **lst_env)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	if ((split = ft_splitwhitespace_shell(str)) == NULL)
		return ;
	while (split[i])
	{
		convert_quote(&(split[i]), lst_env);
		i += 1;
	}
	parser(split, lst, lst_env);
}
