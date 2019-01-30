/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:15:26 by tcollard          #+#    #+#             */
/*   Updated: 2019/01/30 13:46:51 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	fill_input(char **s, int end, int start, t_ast *elem)
{
	int		i;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	if (!(elem->input = (char**)malloc(sizeof(char*) * (end - start + 1))))
		return ;
	while (start < end)
	{
		elem->input[i] = ft_strdup(s[start]);
		start += 1;
		i += 1;
	}
	elem->input[i] = NULL;
	elem->type = CMD;
}

static void	fill_input_redir(char *s, t_ast *elem)
{
	int	i;
	int	save;
	int	wd;

	i = 0;
	save = i;
	wd = 0;
	while (s[i])
		if (ft_isdigit(s[i]) == 1)
		{
			while (ft_isdigit(s[i]) == 1)
				i += 1;
			elem->input[wd] = ft_strsub(s, save, i - save);
			wd += 1;
			save = i;
		}
		else
		{
			while (ft_isoperator(s[i]) == 1)
				i += 1;
			i += (s[i] == '-') ? 1 : 0;
			elem->input[wd] = ft_strsub(s, save, i - save);
			wd += 1;
			save = i;
		}
}

static void	split_redir(char *s, t_ast *elem)
{
	int		wd;
	int		i;

	wd = 0;
	i = 0;
	while (s[i])
		if (ft_isdigit(s[i]) == 1)
		{
			wd += 1;
			while (ft_isdigit(s[i]) == 1)
				i += 1;
		}
		else
		{
			wd += 1;
			while (ft_isoperator(s[i]) == 1)
				i += 1;
			i += (s[i] == '-') ? 1 : 0;
		}
	if (!(elem->input = (char**)malloc(sizeof(char*) * (wd + 1))))
		return ;
	elem->input[wd] = NULL;
	fill_input_redir(s, elem);
}

static void	fill_operator(char **s, int i, int x, t_ast *elem)
{
	int			z;
	size_t		len;
	static char	*operator[16] = {">", ">>", ">>&", "<", "<<<", "<>", "<<",
	"&>", "&>>", ">&", "<&-", ">&-", "&", "|", "&&", "||"};

	z = -1;
	len = 0;
	while (s[i][x + len] && (ft_isoperator(s[i][x + len]) == 1
	|| s[i][x + len] == '-'))
		len += 1;
	while (z++ < 16)
		if (ft_strlen(operator[z]) == len && ft_strncmp(&s[i][x], operator[z],
			len) == 0)
			break ;
	if (z < 7)
		elem->type = REDIR;
	else if (z < 12)
		elem->type = AGREG;
	else if (z < 14)
		elem->type = OPERATOR;
	else
		elem->type = LOGIC;
	split_redir(s[i], elem);
}

void		fill_ast(char **s, t_ast **lst)
{
	t_ast	*new;
	int		i;
	int		x;
	int		save;

	i = -1;
	save = 0;
	new = create_new_elem(lst);
	while (s[++i])
	{
		x = -1;
		while (s[i][++x])
			if (ft_isoperator(s[i][0]) == 1 || (ft_isoperator(s[i][x]) == 1
			&& ft_isdigit(s[i][x - 1]) == 1))
			{
				(new->type != NO_TYPE) ? new = add_new_elem(lst) : 0;
				fill_input(s, i, save, new);
				new = add_new_elem(lst);
				fill_operator(s, i, x, new);
				save = i + 1;
				break ;
			}
	}
	(new->type != NO_TYPE && i != save) ? new = add_new_elem(lst) : 0;
	(i != save) ? fill_input(s, i, save, new) : 0;
}
