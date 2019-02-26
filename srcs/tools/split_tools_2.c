/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:43:14 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/26 17:32:37 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	check_before_operator(char *s, int *i, unsigned int *nb_word)
{
	int x;

	x = 1;
	while (*i - x >= 0 && ft_isdigit(s[*i - x]) == 1)
		x += 1;
	if (*i > 0 && *i - x > 0 && ft_isspace(s[*i - x]) == 0)
		*nb_word += 1;
}

// static void	check_after_operator(char *s, int *i, unsigned int *nb_word,
// 	size_t len)
// {
// 	int	x;
//
// 	x = 0;
// 	while (s[*i + len + x] && ft_isdigit(s[*i + len + x]) == 1)
// 		x += 1;
// 	if ((s[*i + len + x] && ft_isspace(s[*i + len + x]) == 0))
// 	// || (s[*i + len] == '-' && s[*i + len - 1] != '&'))
// 		*nb_word += 1;
// }

int			check_operator(char *s, int *i, unsigned int *nb_word, size_t len)
{
	int			x;
	static char	*operator[15] = {">>", ">>&", ">&", ">", "<<<", "<<",
	"<>", "<", "<&", "&>>", "&>", "&&", "&", "||", "|"};

	x = 0;
	while (x < 15)
	{
		if (ft_strlen(operator[x]) == len && ft_strncmp(&s[*i], operator[x],
			len) == 0)
			break ;
		x += 1;
	}
	if (x == 15)
		return (ft_error_redir_format(&s[*i], len));
	else if (x >= 9)
	{
		*nb_word += (*i > 0 && ft_isspace(s[*i - 1]) == 0) ? 1 : 0;
		// *i += len;
		// *nb_word += (s[*i + len] && ft_isspace(s[*i + len]) == 0 && x != 9 && x != 10) ? 1 : 0;
	}
	else
	{
		check_before_operator(s, i, nb_word);
		// check_after_operator(s, i, nb_word, len);
	}
	return (1);
}

int			type_operator(char const *s, int *i)
{
	int			x;
	size_t		len;
	static char	*operator[15] = {">>", ">>&", ">&", ">", "<<<", "<<",
	"<>", "<", "<&", "&>>", "&>", "&&", "&", "||", "|"};

	x = 0;
	len = 0;
	while (s[*i + len] && ft_isoperator(s[*i + len]) == 1)
		len += 1;
	// if (s[*i + len] == '-' && s[*i + len - 1] == '&' &&
	// (ft_isspace(s[*i + len + 1]) == 1 || !s[*i + len + 1]))
	// 	len += 1;
	while (x < 15)
	{
		if (ft_strlen(operator[x]) == len && ft_strncmp(&s[*i], operator[x],
			len) == 0)
			break ;
		x += 1;
	}
	if (x >= 9)
		return (1);
	return (0);
}

void		get_position(char const *s, int *i, int wn, int *iw)
{
	int	x;

	x = 0;
	// if (s[*i] == '-' && s[*i - 1] == '&' && ft_isspace(s[*i + 1]) == 1)
	// {
	// 	*i += 2;
	// 	if ((*iw += 1) == wn)
	// 		return ;
	// }
	// ft_printf("GET POS |%s|\n", &s[*i]);
	if (s[*i] == '-')
	{
		if ((*iw += 1) == wn)
			return ;
		*i += 1;
		return ;
	}
	else
	{
		while (s[*i + x] && ft_isdigit(s[*i + x]) == 1)
			x += 1;
		if (s[*i + x] && ft_isspace(s[*i + x]) == 0)
			*iw += 1;
		else
			*i += x;
	}
}
