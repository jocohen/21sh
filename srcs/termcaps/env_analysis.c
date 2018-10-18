/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:08:52 by jocohen           #+#    #+#             */
/*   Updated: 2018/06/24 10:56:47 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_list	*find_var(t_list *fp, char *var)
{
	int		y;

	while (fp)
	{
		y = 0;
		while (((char *)fp->content)[y] && ((char *)fp->content)[y] != '=')
			y += 1;
		if (((char *)(fp->content))[y] == '=')
		{
			((char *)fp->content)[y] = 0;
			if (!(ft_strcmp(fp->content, var)))
			{
				((char *)fp->content)[y] = '=';
				return (fp);
			}
			((char *)fp->content)[y] = '=';
		}
		fp = fp->next;
	}
	return (0);
}

char	*find_var_value(t_list *fp, char *var)
{
	int		y;

	while (fp)
	{
		y = 0;
		while (((char *)fp->content)[y] && ((char *)fp->content)[y] != '=')
			y += 1;
		if (((char *)(fp->content))[y] == '=')
		{
			((char *)fp->content)[y] = 0;
			if (!(ft_strcmp(fp->content, var)))
			{
				((char *)fp->content)[y] = '=';
				return (fp->content + (y + 1));
			}
			((char *)fp->content)[y] = '=';
		}
		fp = fp->next;
	}
	return (0);
}

int		env_to_lst(char **s, t_list **fp)
{
	int		x;
	t_list	*tmp;

	x = 0;
	if (s && s[x])
	{
		if (!(tmp = ft_lstnew(s[x], ft_strlen(s[x]) + 1)))
			return (0);
		x += 1;
		*fp = tmp;
	}
	while (s && s[x])
	{
		if (!(tmp->next = ft_lstnew(s[x], ft_strlen(s[x]) + 1)))
			return (lst_deletion(fp));
		x += 1;
		tmp = tmp->next;
	}
	return (1);
}

char	**lst_to_env(t_list *fp)
{
	t_list	*tmp;
	char	**s;
	size_t	x;

	tmp = fp;
	x = 0;
	while (tmp)
	{
		x += 1;
		tmp = tmp->next;
	}
	if (!(s = (char **)malloc(sizeof(char *) * (x + 1))))
		return (0);
	x = 0;
	while (fp)
	{
		s[x++] = fp->content;
		fp = fp->next;
	}
	s[x] = 0;
	return (s);
}

int		all_path_exec(t_list *fp, char *blt_in, char ***out)
{
	int		x;
	char	*s;

	s = find_var_value(fp, "PATH");
	if (!s || !(*s))
		return (2);
	if (!((*out) = ft_strsplit(s, ':')))
		return (0);
	s = 0;
	x = 0;
	while ((*out)[x])
	{
		if (!(s = ft_path((*out)[x], blt_in)))
		{
			ft_memdel2(out);
			return (0);
		}
		ft_memdel((void **)&(*out)[x]);
		(*out)[x++] = s;
	}
	return (1);
}
