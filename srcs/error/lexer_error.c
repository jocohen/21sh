/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 11:52:14 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/13 14:48:52 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_error_splitshell(void)
{
	write(2, "21sh: parse error near `;;'\n", 28);
	g_ret[0] = 1;
	return (-1);
}

int	ft_error_redir_format(char *ope, int len)
{
	int			i;
	int			size;
	int			save;
	static char	*operator[16] = {">>", ">>&", ">&-", ">&", ">", "<<<", "<<",
	"<>", "<&-", "<", "&>>", "&>", "&&", "&", "||", "|"};

	i = 0;
	save = -1;
	size = 1;
	while (i < 16)
	{
		if (ft_strncmp(operator[i], ope, size) == 0)
		{
			save = i;
			i = 0;
			size += 1;
		}
		i += 1;
	}
	write(2, "21sh: parse error near `", 24);
	write(2, &ope[size - 1], (len - size == 0) ? 1 : 2);
	write(2, "'\n", 2);
	g_ret[0] = 1;
	return (-1);
}
