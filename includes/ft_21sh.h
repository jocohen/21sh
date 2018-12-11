/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:58:47 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/11 18:42:57 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
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
	int				print;
	int				fd[2];
	int				type;
	char			**input;
	struct s_ast	*back_quote;
	struct s_ast	*next;
	struct s_ast	*back;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef	struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef int			(*t_dispatch)(t_ast*, t_env **lst_env,  char **tab_path);
typedef int			(*t_builtins)(t_ast *elem, t_env **lst_env);

/*
** LEXER:
*/
void				lexer(char *input, t_env **lst_env);
void				clean_input(char *str, t_ast *lst, t_env **lst_env);
void				check_closing_quote(char *c, char *s, char **input);
void				check_cmd_pipe(char **input);
void				find_closing(char **str, int *i);
char				**ft_splitwhitespace_shell(char *s);
char				**ft_strsplit_shell(char *str, char c);
int					convert_quote(char **s, t_env **lst_env);
void				remove_quote(char **s, int *i, t_env *lst_env);

/*
** PARSER:
*/
void				parser(char **input, t_ast *lst, t_env **lst_env);
void				fill_ast(char **s, t_ast **lst);
void				replace_quote(char *s, int *i);
int					analyzer(t_ast *sort, t_env **lst_env);

/*
**	BUILTINS:
*/

/*
** 		ECHO:
*/
int					echo_builtins(t_ast *elem, t_env **lst_env);
/*
** 		CD:
*/
int					cd_builtins(t_ast *elem, t_env **lst_env);
/*
** 		SETENV:
*/
int					setenv_builtins(t_ast *elem, t_env **lst_env);
/*
** 		UNSETENV:
*/
int					unsetenv_builtins(t_ast *elem, t_env **lst_env);
/*
** 		ENV:
*/
void				env_cp(char **env, t_env **lst_env);
int					env_builtins(t_ast *elem, t_env **lst_env);
char				*get_env_value(t_env *lst_env, char *str);
void				convert_lst_tab(t_env *lst_env, char ***tab);

/*
**	EXEC INPUT:
*/
int					exec_input(t_ast *elem, t_env *lst_env, char **tab_path);

/*
**	OPERATOR:
*/
int					do_pipe(t_ast *elem, t_env **lst_env);
int					job_control(t_ast *elem, t_env *lst_env);

/*
** ERROR:
*/
int					exec_error(int err, char *files);
int					ft_error_parse_redir(char **input);
int					ft_error_splitshell(void);
int					ft_error_redir_format(char *ope, int len);
int					error_cd(char *err, int type);
int					error_setenv(int i);
int					error_unsetenv(int i, char *s);

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
int					dispatch_cmd(t_ast *elem, t_env **lst_env, char **tab_path);
int					dispatch_logic(t_ast *elem, t_env **lst_env, char **tab_path);
int					dispatch_redir(t_ast *elem, t_env **lst_env, char **tab_path);
int					dispatch_operator(t_ast *elem, t_env **lst_env,
					char **tab_path);
int					dispatch_agreg(t_ast *elem, t_env **lst_env, char **tab_path);

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
** 		env:
*/
t_env				*find_elem_env(t_env **lst, char *key);
t_env				*get_last_elem_env(t_env **lst);
void				add_shlvl(t_env **lst);
void				add_elem_env(t_env **lst, char *key, char *value);
void				display_env(t_env *lst);

/*
**		clean:
*/
void				delete_str_tab(char **tab);
void				del_lst_env(t_env **lst);
void				del_double_tab(char **tab1, char **tab2);
void				del_lst_ast(t_ast **lst);

/*
** OTHER:
*/
void				check_opening_quote(char **str);
void				init_ast(char **input, char *s);
char				*missing_quote_prompt(char c);
int					main(int argc, char **argv, char **env);

#endif
