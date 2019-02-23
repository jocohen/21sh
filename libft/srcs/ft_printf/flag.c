/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:50:35 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/23 16:23:59 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	check_flag(t_flag *tab_p)
{
	if (tab_p->flag[3] == 1)
		tab_p->flag[4] = 0;
	if (tab_p->flag[2] == 1)
		tab_p->flag[1] = 0;
}

void	add_flag(char *str, size_t *i, t_flag *tab_p)
{
	while (str[*i] == '-' || str[*i] == '0' || str[*i] == '+'
			|| str[*i] == ' ' || str[*i] == '#')
	{
		if (str[*i] == '#')
			tab_p->flag[0] = 1;
		if (str[*i] == '0')
			tab_p->flag[1] = 1;
		if (str[*i] == '-')
			tab_p->flag[2] = 1;
		if (str[*i] == '+')
			tab_p->flag[3] = 1;
		if (str[*i] == ' ')
			tab_p->flag[4] = 1;
		*i += 1;
	}
	check_flag(tab_p);
}

char	*dispatch_flag(t_flag *tab_p, char *v, char c)
{
	char	*add;
	char	*modif;
	char	z;
	int		len;

	z = ' ';
	(tab_p->flag[3] == 1 && *v != '%' && c != 's') ? v = plus(&v, c, tab_p) : 0;
	(tab_p->flag[0] == 1 && *v != '%') ? v = hashtag(&v, c, tab_p) : 0;
	(tab_p->flag[1] == 1 && (tab_p->precision == -1 || c == 's' || *v == '%'))
		? v = zero(&v, c, tab_p) : 0;
	(tab_p->flag[2] == 1) ? v = minus(&v, c, tab_p) : 0;
	(tab_p->flag[4] == 1) ? v = space(&v, c, tab_p) : 0;
	len = (int)ft_strlen(v);
	modif = ft_strdup(v);
	if (tab_p->width > len)
	{
		(len == 0 && tab_p->flag[1] == 1) ? z = '0' : 0;
		if (!(add = ft_memalloc(tab_p->width - len + 1)))
			return (NULL);
		ft_memdel((void **)&v);
		v = ft_strjoin(ft_memset(add, z, tab_p->width - len), modif);
		ft_memdel((void **)&add);
	}
	ft_memdel((void **)&modif);
	return (v);
}
