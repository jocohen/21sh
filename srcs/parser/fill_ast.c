/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 10:38:22 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/16 18:42:46 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static void		fill_type_ast(char *s, t_ast *elem)
{
	if (elem->type == NO_TYPE)
	{
		if (s[0] == '<' || s[0] == '>')
			elem->type = (s[1] != '&') ? REDIR : AGGREG;
		else if (s[0] == '|' || s[0] == '&')
			elem->type = (s[1] == '\0') ? OPERATOR : LOGIC;
		else
			elem->type = CMD;
		elem->value = ft_strdup(s);
	}
}

static void		fill_opt(char *s, t_ast *elem)
{
	char	*tmp;

	tmp = NULL;
	if (elem->opt == NULL)
		elem->opt = ft_strdup(s);
	else
	{
		tmp = ft_strjoin(elem->opt, " ");
		free(elem->opt);
		elem->opt = ft_strjoin(tmp, s);
		free(tmp);
	}
}

static void		fill_content(char *s, t_ast *elem)
{
	char	*tmp;

	tmp = NULL;
	if (elem->content == NULL)
		elem->content = ft_strdup(s);
	else
	{
		tmp = ft_strjoin(elem->content, " ");
		free(elem->content);
		elem->content = ft_strjoin(tmp, s);
		free(tmp);
	}
}

void			fill_ast(char *s, t_ast **lst)
{
	t_ast	*new;

	new = (*lst == NULL) ? create_new_elem(lst) : get_last_elem(lst);
	(new->type == LOGIC || new->type == OPERATOR) ? new = add_new_elem(lst) : 0;
	if (new->type == NO_TYPE)
		fill_type_ast(s, new);
	else if (s[0] == '-' && new->type != NO_TYPE && new->content == NULL)
		fill_opt(s, new);
	else if (s[0] == '<' || s[0] == '>' || s[0] == '&' || s[0] == '|')
	{
		new = add_new_elem(lst);
		fill_type_ast(s, new);
	}
	else
		fill_content(s, new);
}
