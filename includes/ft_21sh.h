/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:58:47 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 12:15:36 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
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
# define AGREG	4

typedef	struct		s_ast
{
	int				type;
	char			**input;
	struct s_ast	*back_quote;
	struct s_ast	*next;
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
void				convert_quote(char **s, char **tab_env);
void				remove_quote(char **s, int *i, char **tab_env);

/*
** PARSER:
*/
void				parser(char **input, t_ast *lst, char **tab_env);
void				fill_ast(char **s, t_ast **lst);
void				replace_quote(char *s, int *i);
void				analyzer(t_ast *lst, char **tab_env);

/*
**	BUILTINS:
*/

/*
** 		ECHO:
*/
void				echo_builtins(t_ast *elem, char **tab_env);
/*
** 		CD:
*/
void				cd_builtins(t_ast *elem, char **tab_env);
/*
** 		SETENV:
*/
void				setenv_builtins(t_ast *elem, char **tab_env);
/*
** 		UNSETENV:
*/
void				unsetenv_builtins(t_ast *elem, char **tab_env);
/*
** 		ENV:
*/
void				env_cp(char **env, char ***tab_env);
void				env_builtins(t_ast *elem, char **tab_env);
char				*get_env_value(char **tab, char *str);

/*
**	EXEC INPUT:
*/
void				exec_input(char **tab, t_ast *elem);

/*
** ERROR:
*/
int					exec_error(int err, char *files);
int					ft_error_parse_redir(char **input);
int					ft_error_splitshell(void);
int					ft_error_redir_format(char *ope, int len);


/*
** TOOLS:
**
**	 	lexer:
*/
int					ft_isquote(char c);
int					ft_isoperator(char c);
void				ft_insert(char **source, char *insert, int pos1, int pos2);
void				ft_delete_inside(char **source, int start, int len);

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
void				dispatch_agreg(t_ast *elem, char **tab_env);

/*
** 		split:
*/
void				in_quote(char const *s, int *i);
void				lettre_in_quote(char const *s, int *i, int *nb_lettre);
void				nb_lettre_operator(char *s, int i, int *nb_lettre);
// void				lettre_operator(char const *s, int *i, int *nb_lettre);
int					check_redir(char *s, int *i, unsigned int *nb_word);
int					check_operator(char *s, int *i, unsigned int *nb_word, size_t len);
int					position_redir(char const *s, int *i, int wn, int *iw);
int					type_operator(char const *s, int *i);
void				get_position(char const *s, int *i, int wn, int *iw);

/*
**		clean:
*/
void				delete_str_tab(char **tab);

/*
** OTHER:
*/
void				check_opening_quote(char **str);
void				init_ast(char **input, char *s);
char				*missing_quote_prompt(char c);
int					main(int argc, char **argv, char **env);

#endif
