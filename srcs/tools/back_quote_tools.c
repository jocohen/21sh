/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_quote_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:59:13 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/22 21:47:41 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*get_back_quote_exec(int fd)
{
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
	{
		if (!sub)
			(!(sub = ft_strdup(str))) ? ft_exit_malloc() : 0;
		else
		{
			(!(tmp = ft_strjoin(sub, " "))) ? ft_exit_malloc() : 0;
			ft_memdel((void **)&sub);
			(!(sub = ft_strjoin(tmp, str))) ? ft_exit_malloc() : 0;
			ft_memdel((void **)&tmp);
		}
		ft_memdel((void **)&str);
	}
	close(fd);
	return (sub);
}

static int	lexer_back_quote(char *input, t_env **lst_env, t_alloc *alloc)
{
	int		i;
	char	**lexer;
	t_ast	*lst;

	i = 0;
	lexer = NULL;
	lst = NULL;
	if (!check_opening_quote(&input, alloc) || !check_cmd_pipe(&input, alloc))
	{
		ft_memdel((void **)&input);
		return (0);
	}
	i = (input[i] == ';' && input[i + 1] != ';') ? 1 : 0;
	if ((lexer = ft_strsplit_shell(&input[i], ';')) == NULL)
	{
		ft_memdel((void **)&input);
		return (0);
	}
	set_terminal(1);
	read_lexer(lexer, lst_env, lst, &alloc);
	set_terminal(0);
	ft_memdel((void **)&input);
	return (1);
}

char		*ft_back_quote(char *sub, t_env *lst_env, t_alloc **alloc)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strjoin(sub, " > /tmp/.back_quote.txt");
	ft_memdel((void **)&sub);
	if (!lexer_back_quote(str, &lst_env, *alloc))
		return (0);
	sub = get_back_quote_exec(0);
	while (sub && sub[i])
		if (sub[i] == ' ' && sub[i + 1] == ' ')
			ft_custom_memmove(&sub[i], &sub[i + 1], ft_strlen(&sub[i + 1]));
		else
			i += 1;
	return (sub);
}
