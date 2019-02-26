/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:15:26 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/26 18:46:18 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	fill_input_redir(char **s, t_ast *elem, int *pos, int nb_wd)
{
	int		i;
	int		save;
	int		wd;

	i = 0;
	save = i;
	wd = 0;
	while (s[*pos][i])
	{
		if (ft_isdigit(s[*pos][i]) == 1)
			wd += get_last_digit(&i, s[*pos], &save, &(elem->input[wd]));
		else if (ft_isoperator(s[*pos][i]) == 1)
		{
			// ft_printf("GET LAST OP\ns[%d] = |%s|\nwd = %d\n", *pos, s[*pos], wd);
			wd += get_last_operator(&i, s[*pos], &save, &(elem->input[wd]));
			// ft_printf("input[0]: |%s|\n", elem->input[0]);
		}
		else
			wd += get_last_index(&i, s[*pos], &save, &(elem->input[wd]));
	}
	// ft_printf("wd = %d\n", wd);
	if (wd < nb_wd)
	{
		*pos += 1;
		elem->input[wd] = ft_strdup(s[*pos]);
		elem->input[wd + 1] = NULL;
	}
	else
	{
		elem->input[wd] = NULL;
	}
}

static void	split_redir(char **s, t_ast *elem, int *pos)
{
	int		wd;
	int		i;

	wd = 0;
	i = 0;
	while (s[*pos][i])
		if (ft_isdigit(s[*pos][i]) == 1)
		{
			wd += 1;
			while (ft_isdigit(s[*pos][i]) == 1)
				i += 1;
		}
		else if (ft_isoperator(s[*pos][i]) == 1)
		{
			wd += 1;
			while (ft_isoperator(s[*pos][i]) == 1)
				i += 1;
			if (s[*pos][i] == '-')
			{
				i += 1;
				wd += 1;
			}
		}
		else
			get_last_index_split(&i, s[*pos], &wd);
	if (elem->type <= AGREG)
		wd += 1;
	// ft_printf("split redir wd = %d\n", wd);
	if (!(elem->input = (char**)malloc(sizeof(char*) * (wd + 1))))
		ft_exit_malloc();
	elem->input[wd] = NULL;
	fill_input_redir(s, elem, pos, wd);
}

static int	fill_operator(char **s, int x, t_ast *elem, int *i)
{
	int			z;
	size_t		len;
	static char	*operator[16] = {">", ">>", ">>&", "<", "<<<", "<>", "<<",
	"&>", "&>>", ">&", "<&-", ">&-", "&", "|", "&&", "||"};

	z = -1;
	len = 0;
	while (s[*i][x + len] && (ft_isoperator(s[*i][x + len]) == 1 || s[*i][x + len] == '-'))
		len += 1;
	while (z++ < 16)
		if (ft_strlen(operator[z]) == len && ft_strncmp(&s[*i][x], operator[z],
			len) == 0)
			break ;
	if (z < 6)
		elem->type = REDIR;
	else if (z == 6)
		elem->type = HEREDOC;
	else if (z < 12)
		elem->type = AGREG;
	else if (z < 14)
		elem->type = OPERATOR;
	else
		elem->type = LOGIC;
	split_redir(s, elem, i);
	return (1);
}


// static void	fill_input_redir(char *s, t_ast *elem)
// {
// 	int		i;
// 	int		save;
// 	int		wd;
//
// 	i = 0;
// 	save = i;
// 	wd = 0;
// 	while (s[i])
// 		if (ft_isdigit(s[i]) == 1)
// 			wd += get_last_digit(&i, s, &save, &(elem->input[wd]));
// 		else if (ft_isoperator(s[i]) == 1)
// 			wd += get_last_operator(&i, s, &save, &(elem->input[wd]));
// 		else
// 			wd += get_last_index(&i, s, &save, &(elem->input[wd]));
// }
//
// static void	split_redir(char *s, t_ast *elem)
// {
// 	int		wd;
// 	int		i;
//
// 	wd = 0;
// 	i = 0;
// 	while (s[i])
// 		if (ft_isdigit(s[i]) == 1)
// 		{
// 			wd += 1;
// 			while (ft_isdigit(s[i]) == 1)
// 				i += 1;
// 		}
// 		else if (ft_isoperator(s[i]) == 1)
// 		{
// 			wd += 1;
// 			while (ft_isoperator(s[i]) == 1)
// 				i += 1;
// 			i += (s[i] == '-') ? 1 : 0;
// 		}
// 		else
// 			get_last_index_split(&i, s, &wd);
// 	if (!(elem->input = (char**)malloc(sizeof(char*) * (wd + 1))))
// 		ft_exit_malloc();
// 	elem->input[wd] = NULL;
// 	fill_input_redir(s, elem);
// }
//
// static int	fill_operator(char *s, int x, t_ast *elem)
// {
// 	int			z;
// 	size_t		len;
// 	static char	*operator[16] = {">", ">>", ">>&", "<", "<<<", "<>", "<<",
// 	"&>", "&>>", ">&", "<&-", ">&-", "&", "|", "&&", "||"};
//
// 	z = -1;
// 	len = 0;
// 	while (s[x + len] && (ft_isoperator(s[x + len]) == 1 || s[x + len] == '-'))
// 		len += 1;
// 	while (z++ < 16)
// 		if (ft_strlen(operator[z]) == len && ft_strncmp(&s[x], operator[z],
// 			len) == 0)
// 			break ;
// 	if (z < 6)
// 		elem->type = REDIR;
// 	else if (z == 6)
// 		elem->type = HEREDOC;
// 	else if (z < 12)
// 		elem->type = AGREG;
// 	else if (z < 14)
// 		elem->type = OPERATOR;
// 	else
// 		elem->type = LOGIC;
// 	split_redir(s, elem);
// 	return (1);
// }


static int	go_end_quote(char **s, int i, int *x)
{
	char	c;

	c = s[i][*x];
	*x += 1;
	while (s[i][*x] && s[i][*x] != c)
		*x += 1;
	*x += 1;
	return (1);
}

void		fill_ast(char **s, t_ast **lst, int save)
{
	// t_ast	*new;
	// 	int		i;
	// 	int		x;
	//
	// 	i = -1;
	// 	new = create_new_elem(lst);
	// 	while (s[++i])
	// 	{
	// 		x = -1;
	// 		while (s[i][++x])
	// 			if (ft_isoperator(s[i][0]) == 1 || (ft_isoperator(s[i][x]) == 1
	// 			&& x - 1 >= 0 && ft_isdigit(s[i][x - 1]) == 1))
	// 			{
	// 				(new->type != NO_TYPE) ? new = add_new_elem(lst) : 0;
	// 				(ft_isoperator(s[save][0]) == 0) ?
	// 				fill_input(s, i, save, new) : 0;
	// 				(ft_isoperator(s[save][0]) == 0) ? new = add_new_elem(lst) : 0;
	// 				save = i + fill_operator(s[i], x, new);
	// 				break ;
	// 			}
	// 			else if (ft_isquote(s[i][x]) == 1 && go_end_quote(s, i, &x) == 1)
	// 				break ;
	// 	}
	// 	(new->type != NO_TYPE && i != save) ? new = add_new_elem(lst) : 0;
	// 	(i != save) ? fill_input(s, i, save, new) : 0;

	t_ast	*new;
	int		i;
	int		x;

	i = -1;
	new = create_new_elem(lst);
	while (s[++i])
	{
		x = -1;
		while (s[i][++x])
			if (ft_isoperator(s[i][0]) == 1 || (ft_isoperator(s[i][x]) == 1
			&& x - 1 >= 0 && ft_isdigit(s[i][x - 1]) == 1))
			{
				(new->type != NO_TYPE) ? new = add_new_elem(lst) : 0;
				(ft_isoperator(s[save][0]) == 0) ?
				fill_input(s, i, save, new) : 0;
				(ft_isoperator(s[save][0]) == 0) ? new = add_new_elem(lst) : 0;
				save = i + fill_operator(s, x, new, &i) + ((new->type > AGREG) ? 0 : 1);
				break ;
			}
			else if (ft_isquote(s[i][x]) == 1 && go_end_quote(s, i, &x) == 1)
				break ;
	}
	if (new->type > AGREG)
		new = add_new_elem(lst);
	if (new->type == NO_TYPE)
 		fill_input(s, i, save, new);
	else if (i != save)
		add_input_prev_cmd(s, i, save, new);
}
