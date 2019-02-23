/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:56:54 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/23 13:01:31 by tcollard         ###   ########.fr       */
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
			while (s[*i] && s[*i] != c)
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

void	add_input_prev_cmd(char **s, int end, int start, t_ast *elem)
{
	char	**tmp;
	int		len;
	int		i;
	int		init_len;

	len = 0;
	i = 0;
	tmp = NULL;
	// ft_printf("start = %d\n", start);
	//RECHERCHE DU PREMIER ELEM DE TYPE CMD EN PARTANT DE LA FIN
	while (elem->back && elem->type != CMD)
		elem = elem->back;
	// //SAVE DU TAB INPUT ORIGINAL AFIN DE FAIRE UN TAB JOIN DANS L'IDEE
	// tmp = &(elem->input);
	while (elem->input[len])
	{
		// ft_printf("IN[%d]: %s\n", len, elem->input[len]);
		len += 1;
	}
	// ft_printf("OK1\n");
	init_len = len;
	len += end - start;
	if (!(tmp = (char**)malloc(sizeof(char*) * len)))
		ft_exit_malloc();
	// start += 1;
	// ft_printf("OK2\nlen = %d\n", len);
	// ft_printf("tmp[%d]: |%s|\n", i, *tmp[i]);
	while (elem->input[i])
	{
		// ft_printf("tmp[%d]: |%s|\n", i, (*tmp)[i]);
		tmp[i] = ft_strdup(elem->input[i]);
		i += 1;
	}
	// ft_printf("OK3    i = %d\n", i);
	while (i < len)
	{
		tmp[i] = ft_strdup(s[start]);
		start += 1;
		i += 1;
	}
	// ft_printf("OK4\n");
	delete_str_tab(elem->input);
	elem->input = tmp;
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
	// ft_printf("len = %d\n", len);
	if (!(elem->input = (char**)malloc(sizeof(char*) * len)))
		ft_exit_malloc();
	while (start < end && i < len - 1)
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
	if (elem->back && len == 2 && end - start != 2)
		add_input_prev_cmd(s, end, start, elem);
}
