/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:16:32 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/29 18:24:02 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	delete_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i += 1;
	}
	free(tab);
	tab = NULL;
}

void	del_lst_env(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	if (!lst)
		return ;
	while (tmp)
	{
		*lst = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = *lst;
	}
	*lst = NULL;
}

void	del_lst_ast(t_ast **lst)
{
	t_ast	*tmp;
	int		i;

	i = 0;
	tmp = *lst;
	if (!lst)
		return ;
	while (tmp)
	{
		*lst = tmp->next;
		delete_str_tab(tmp->input);
		free(tmp);
		tmp = *lst;
	}
}

void	del_double_tab(char **tab1, char **tab2)
{
	if (tab1)
		delete_str_tab(tab1);
	if (tab2)
		delete_str_tab(tab2);
}
