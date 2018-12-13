/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:44:25 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/13 16:44:18 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// t_env	*add_var_env(char *var, char *value, t_env **fp)
// {
// 	t_env *tmp;
//
// 	tmp = *fp;
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	if (!tmp)
// 	{
// 		if (!(tmp = ft_lstnew(0, 0)))
// 			return (0);
// 		(!*fp) ? *fp = tmp : 0;
// 	}
// 	else
// 	{
// 		if (!(tmp->next = ft_lstnew(0, 0)))
// 			return (0);
// 		tmp = tmp->next;
// 	}
// 	if (!(tmp->content = ft_memalloc(ft_strlen(var) + ft_strlen(value) + 2)))
// 		return (0);
// 	tmp->content_size = ft_strlen(var) + ft_strlen(value) + 2;
// 	ft_strcat(ft_strcat(ft_strcpy(tmp->content, var), "="), value);
// 	return (tmp);
// }

// int		change_value(t_env *tmp, char *value)
// {
// 	char	*val;
// 	int		y;
// 	int		x;
//
// 	x = 0;
// 	while (((char *)(tmp->content))[x] != '=')
// 		x += 1;
// 	if (!(val = ft_memalloc(x + ft_strlen(value) + 2)))
// 		return (0);
// 	y = x + 1;
// 	while (x != -1)
// 	{
// 		val[x] = ((char *)(tmp->content))[x];
// 		x -= 1;
// 	}
// 	x = 0;
// 	while (value && value[x])
// 		val[y++] = value[x++];
// 	ft_memdel((void **)&(tmp->content));
// 	tmp->content = val;
// 	return (1);
// }
