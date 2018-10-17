/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:58:47 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/17 17:55:05 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"

/*
** # define FALSE 0
** # define TRUE 1
*/

# define NO_TYPE -1
# define CMD	0
# define LOGIC	1
# define REDIR	2
# define OPERATOR	3
# define AGGREG	4

typedef	struct		s_ast
{
	int				type;
	char			*value;
	char			*opt;
	char			*content;
	struct s_ast	*back_quote;
	struct s_ast	*next;
	struct s_ast	*prev;
}					t_ast;

typedef void		(*t_dispatch)(t_ast*, char**);

/*
** LEXER:
*/
void				lexer(char *input, char **tab_env);
void				clean_input(char *str, t_ast *lst, char **tab_env);
void				check_closing_quote(char *c, char *s, char **input);
void				check_cmd_pipe(char **input);
void				find_closing(char **str, int *i);
char				**ft_splitwhitespace_shell(char *s);
char				**ft_strsplit_shell(char *str, char c);
void				convert_quote(char **s);
void				remove_quote(char **s, int *i);

/*
** PARSER:
*/
void				parser(char **input, t_ast *lst, char **tab_env);
void				fill_ast(char *s, t_ast **lst);
void				replace_quote(char *s, int *i);
void				analyzer(t_ast *lst, char **tab_env);

/*
**	BUILTINS:
*/
void				builtins_dispatch(t_ast *elem, char **tab_env);

/*
** ENV:
*/
void				env_cp(char **env, char ***tab_env);

/*
** ERROR:
*/
int					ft_error(char *s, int error);
int					ft_error_parse(char *s, int count);

/*
** TOOLS:
**
**	 	lexer:
*/
int					ft_isquote(char c);
void				ft_insert(char **source, char *insert, int pos);

/*
**		parser:
*/
t_ast				*create_new_elem(t_ast **lst);
t_ast				*get_last_elem(t_ast **lst);
t_ast				*add_new_elem(t_ast **lst);
void				check_quote(char *s);
void				replace_quote(char *s, int *i);


/*
** 		analyzer:
*/
void				dispatch_cmd(t_ast *elem, char **tab_env);
void				dispatch_logic(t_ast *elem, char **tab_env);
void				dispatch_redir(t_ast *elem, char **tab_env);
void				dispatch_operator(t_ast *elem, char **tab_env);
void				dispatch_aggreg(t_ast *elem, char **tab_env);

/*
** 		split:
*/
void				in_quote(char const *s, int *i);
void				lettre_in_quote(char const *s, int *i, int *nb_lettre);
void				lettre_operator(char const *s, int *i, int *nb_lettre);
int					check_operator(char *s, int *i, unsigned int *nb_word);
int					position_operator(char const *s, int *i, int wn, int *iw);

/*
** OTHER:
*/
void				check_opening_quote(char **str);
void				init_ast(char **input, char *s);
char				*missing_quote_prompt(char c);
int					main(int argc, char **argv, char **env);

#endif
