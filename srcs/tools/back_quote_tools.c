/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_quote_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:59:13 by tcollard          #+#    #+#             */
/*   Updated: 2019/01/29 18:16:26 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*get_back_quote_exec(void)
{
	int		fd;
	char	*str;
	char	*tmp;
	char	*sub;

	fd = -1;
	str = NULL;
	tmp = NULL;
	sub = NULL;
	if ((fd = open("/tmp/.back_quote.txt", O_RDONLY)) == -1)
		return (sub);
	while (get_next_line(fd, &str) > 0)
		if (!sub)
			sub = ft_strdup(str);
		else
		{
			tmp = ft_strjoin(sub, " ");
			free(sub);
			sub = ft_strjoin(tmp, str);
			free(tmp);
		}
	close(fd);
	return (sub);
}

char		*ft_back_quote(char *sub, t_env *lst_env, t_alloc **alloc)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	str = ft_strjoin(sub, " > /tmp/.back_quote.txt");
	lexer(str, &lst_env, *alloc);
	free(sub);
	sub = get_back_quote_exec();
	while (sub[i])
		if (sub[i] == ' ' && sub[i + 1] == ' ')
			ft_custom_memmove(&sub[i], &sub[i + 1], ft_strlen(&sub[i + 1]));
		else
			i += 1;
	return (sub);
}
