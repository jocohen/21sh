/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:15:26 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/29 14:38:54 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

// static void	fill_type_ast(t_ast *elem)
// {
// 	if (elem->type == NO_TYPE)
// 	{
// 		if (elem->input[0][0] == '<' || elem->input[0][0] == '>')
// 			elem->type = (elem->input[0][1] != '&') ? REDIR : AGREG;
// 		else if (elem->input[0][0] == '|' || elem->input[0][0] == '&')
// 			elem->type = (elem->input[0][0] == '\0') ? OPERATOR : LOGIC;
// 		else
// 			elem->type = CMD;
// 	}
// }
//
// static void	fill_cmd(char **s, int end, int start, t_ast *elem)
// {
// 	int	i;
//
// 	i = 0;
// 	if (!(elem->input = (char **)malloc(sizeof(char *) * (end - start + 1))))
// 	{
// 		ft_printf("Error: malloc fill cmd\n");
// 		return ;
// 	}
// 	while (i < end - start)
// 	{
// 		elem->input[i] = ft_strdup(s[start + i]);
// 		i += 1;
// 	}
// 	elem->input[i] = NULL;
// }

/*
** TO DO:
**		- check if last elem->type == NULL else create new one
**		- read s tab till find operator signe
**		- malloc input sizeof char* and duplicate s** on it
**		- if operator signe, check if digit at the begining or at the end
**			- if there is split in 2 or 3 parts to have fd signe and fd
**			- check if signe exist, if not return error msg and free everything
**
*/

void		fill_ast(char **s, t_ast **lst)
{
	t_ast	*new;
	int		i;
	int		x;

	i= 0;
	x = 0;
	new = (*lst == NULL) ? create_new_elem(lst) : get_last_elem(lst);
	while (s[i])
	{
		while (s[i][x])
			x += 1;
		i += 1;
	}
}

// void		fill_ast(char **s, t_ast **lst)
// {
// 	t_ast	*new;
// 	int		i;
// 	int		save;
//
// 	int x;
// 	x = 0;
//
// 	i = 0;
// 	save = 0;
// 	new = (*lst == NULL) ? create_new_elem(lst) : get_last_elem(lst);
// 	// if (!(new->input = (char**)malloc(sizeof(char*) * 2)))
// 	// {
// 	// 	ft_printf("error malloc\n");
// 	// 	return ;
// 	// }
// 	// new->input[0] = ft_strdup("test de merde");
// 	// new->input[1] = NULL;
// 	(new->type == LOGIC || new->type == OPERATOR) ? new = add_new_elem(lst) : 0;
// 	while (s[i])
// 	{
// 		if (s[i][0] == '<' || s[i][0] == '>' || s[i][0] == '&' ||
// 			s[i][0] == '|')
// 			{
// 				if (new->type != NO_TYPE)
// 				{
// 					ft_printf("add new elem\n");
// 					new = add_new_elem(lst);
// 				}
// 				//JUST HERE MAN !!!!
// 				fill_cmd(s, i, save, new);
// 				fill_type_ast(new);
// 				new = add_new_elem(lst);
// 				fill_cmd(s, i + 1, i, new);
// 				// fill_elem(s, i, new);
// 				fill_type_ast(new);
// 				save = i + 1;
// 				// ft_printf("New elem:\nTYPE =>%d\n", new->type);
// 				// x = 0;
// 				// while (new->input[x])
// 				// {
// 				// 	ft_printf("elem->input[%d]: %s\n", x, new->input[x]);
// 				// 	x += 1;
// 				// }
// 			}
// 		i += 1;
// 	}
// 	if (new->type != NO_TYPE)
// 	{
// 		ft_printf("add new elem\n");
// 		new = add_new_elem(lst);
// 	}
// 	fill_cmd(s, i, save, new);
// 	fill_type_ast(new);
// 	// x = 0;
// 	// ft_printf("New elem:\nTYPE =>%d\n", new->type);
// 	// while (new->input[x])
// 	// {
// 	// 	ft_printf("elem->input[%d]: %s\n", x, new->input[x]);
// 	// 	x += 1;
// 	// }
//
// }
