/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:54:50 by tcollard          #+#    #+#             */
/*   Updated: 2019/01/29 17:55:42 by tcollard         ###   ########.fr       */
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
		if (g_pid == -1)
			break ;
		free(lexer[i]);
		i += 1;
	}
	(lexer != NULL) ? free(lexer) : 0;
}

/*
** exit si ctrl c dans le recall du prompt
*/

void		lexer(char *input, t_env **lst_env, t_alloc *alloc)
{
	int		i;
	char	**lexer;
	t_ast	*lst;

	(void)lst_env;
	i = 0;
	lexer = NULL;
	lst = NULL;
	check_opening_quote(&input, alloc);
	check_cmd_pipe(&input, alloc);
	historic_entry(ft_strdup(input), alloc->history, *lst_env);
	while (input[i] == ';')
		i += 1;
	if ((lexer = ft_strsplit_shell(&input[i], ';')) == NULL)
	{
		ft_memdel((void **)&input);
		return ;
	}
	read_lexer(lexer, lst_env, lst, &alloc);
	ft_memdel((void **)&input);
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
	parser(split, lst, lst_env, alloc);
}
