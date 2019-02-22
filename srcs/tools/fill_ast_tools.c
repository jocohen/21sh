/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:56:54 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/23 00:36:42 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	get_last_index_split(int *i, char *s, int *wd)
{
	char	c;

	c = '\0';
	*wd += 1;
	while (ft_isoperator(s[*i]) == 0)
	{
		if (ft_isquote(s[*i]) == 1)
		{
			c = s[*i];
			while (s[*i] != c)
				*i += 1;
		}
		*i += 1;
	}
}

int		get_last_index(int *i, char *s, int *save, char **input)
{
	char	c;

	c = '\0';
	while (ft_isoperator(s[*i]) == 0)
	{
		if (ft_isquote(s[*i]) == 1)
		{
			c = s[*i];
			*i += 1;
			while (s[*i] != c)
				*i += 1;
		}
		*i += 1;
	}
	*input = (c == '\0') ? ft_strsub(s, *save, *i - *save) :
	ft_strsub(s, *save, *i - *save + 3);
	*save = *i;
	return (1);
}

int		get_last_operator(int *i, char *s, int *save, char **input)
{
	while (ft_isoperator(s[*i]) == 1)
		*i += 1;
	*i += (s[*i] == '-') ? 1 : 0;
	*input = ft_strsub(s, *save, *i - *save);
	*save = *i;
	return (1);
}

int		get_last_digit(int *i, char *s, int *save, char **input)
{
	while (ft_isdigit(s[*i]) == 1)
		*i += 1;
	*input = ft_strsub(s, *save, *i - *save);
	*save = *i;
	return (1);
}

static void	add_input_prev_cmd(char **s, int end, int start, t_ast *elem)
{
	t_ast	*new;
	char	***tmp;
	int		len;
	int		i;

	new = elem;
	len = 0;
	i = 0;
	//RECHERCHE DU PREMIER ELEM DE TYPE CMD EN PARTANT DE LA FIN
	while (elem->back && elem->back->type != CMD)
		elem = elem->back;
	//SAVE DU TAB INPUT ORIGINAL AFIN DE FAIRE UN TAB JOIN DANS L'IDEE
	tmp = &(elem->input);
	while (elem->input[len])
	{
		ft_printf("IN[%d]: %s\n", len, elem->input[len]);
		len += 1;
	}
	ft_printf("OK1\n");
	len += end - start;
	if (!(elem->input = (char**)malloc(sizeof(char*) * len)))
		ft_exit_malloc();
	start += 1;
	ft_printf("OK2\nlen = %d\n", len);
	while ((*tmp)[i])
	{
		elem->input[i] = ft_strdup((*tmp)[i]);
		i += 1;
	}
	ft_printf("OK3\n");
	while (start < len)
	{
		elem->input[i] = ft_strdup(s[i]);
		start += 1;
		i += 1;
	}
	ft_printf("OK4\n");
	delete_str_tab(*tmp);
}

void	fill_input(char **s, int end, int start, t_ast *elem)
{
	int		i;
	t_ast	*tmp;
	int		len;

	i = 0;
	tmp = NULL;
	if (elem->back && elem->back->type <= AGREG)
		len = 2;
	else
		len = end - start + 1;
	if (!(elem->input = (char**)malloc(sizeof(char*) * len)))
		ft_exit_malloc();
	while (start < end && i < len)
	{
		if (!(elem->input[i] = ft_strdup(s[start])))
			ft_exit_malloc();
		start += 1;
		i += 1;
	}
	elem->input[i] = NULL;
	elem->type = CMD;
	//SI AVANT TYPE AGREG OU PLUS BAS
	//RECHERCHE DE L'INPUT DE CMD LE PLUS PROCHE POUR LE MODIF
	if (len == 2 && end - start != 2)
		add_input_prev_cmd(s, end, start, elem);
}
