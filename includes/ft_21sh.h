/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:58:47 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/19 11:06:21 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "../libft/includes/libft.h"

# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdlib.h>

/*
** # define FALSE 0
** # define TRUE 1
*/

# define NO_TYPE 	-1
# define CMD		0
# define LOGIC		1
# define REDIR		2
# define OPERATOR	3
# define AGGREG		4

typedef	struct			s_ast
{
	int					type;
	char				*value;
	char				*opt;
	char				*content;
	struct s_ast		*back_quote;
	struct s_ast		*next;
	struct s_ast		*prev;
}						t_ast;

typedef void			(*t_dispatch)(t_ast*, t_list**);

typedef struct			s_buf
{
	char				*s;
	size_t				x;
	size_t				buf_size;
}						t_buf;

typedef struct			s_historic
{
	char				*origin;
	char				*modif;
	struct s_historic	*next;
	struct s_historic	*prev;
}						t_historic;

int						g_pid;

/*
**	TERMCAPS:
*/
int						env_to_lst(char **s, t_list **fp);
char					*find_var_value(t_list *fp, char *var);
void					ft_exit(int status);
void					set_terminal(t_list *fp, int reset);
void					prompt(t_list **lst, t_historic **history);
void					*ft_realloc(void *ptr, size_t size, size_t len);
void					caller_display(t_list *fp);
void					escape_analysis(t_buf *input, char c, size_t y,
						t_historic **history);
void					del_char(t_buf *input, int type);
int						ft_writestdin(int c);
int						lst_deletion(t_list **fp);
char					*get_end_pwd(char *pwd);
void					enter_section(t_buf *input, t_list **lst,
						t_historic **history, int read);
void					sig_c(int sig);
int						quit_signal(char **av);
int						init_hist(t_historic **history, t_list *lst);
void					historic_move(t_buf *input, t_historic **history,
						int direction);
char					check_prev_read(char k);
int						ft_del_hist(t_historic **fp);
void					reset_hist(t_historic *tmp);
t_historic				*ft_new_cmd_hist(void);
void					check_over_buffer(t_buf *input, char *into_buff);


/*
** LEXER:
*/
void					lexer(char *input, t_list **env);
void					clean_input(char *str, t_ast *lst, t_list **env);
void					check_closing_quote(char *c, char *s, char **input);
void					check_cmd_pipe(char **input);
void					find_closing(char **str, int *i);
char					**ft_splitwhitespace_shell(char *s);
char					**ft_strsplit_shell(char *str, char c);
void					convert_quote(char **s);
void					remove_quote(char **s, int *i);

/*
** PARSER:
*/
void					parser(char **input, t_ast *lst, t_list **env);
void					fill_ast(char *s, t_ast **lst);
void					replace_quote(char *s, int *i);
void					analyzer(t_ast *lst, t_list **env);

/*
**	BUILTINS:
*/
void					builtins_dispatch(t_ast *elem, t_list **env);

/*
** ENV:
*/


/*
** ERROR:
*/
int						ft_error(char *s, int error);
int						ft_error_parse(char *s, int count);

/*
** TOOLS:
**
**	 	lexer:
*/
int						ft_isquote(char c);
void					ft_insert(char **source, char *insert, int pos);

/*
**		parser:
*/
t_ast					*create_new_elem(t_ast **lst);
t_ast					*get_last_elem(t_ast **lst);
t_ast					*add_new_elem(t_ast **lst);
void					check_quote(char *s);
void					replace_quote(char *s, int *i);


/*
** 		analyzer:
*/
void					dispatch_cmd(t_ast *elem, t_list **env);
void					dispatch_logic(t_ast *elem, t_list **env);
void					dispatch_redir(t_ast *elem, t_list **env);
void					dispatch_operator(t_ast *elem, t_list **env);
void					dispatch_aggreg(t_ast *elem, t_list **env);

/*
** 		split:
*/
void					in_quote(char const *s, int *i);
void					lettre_in_quote(char const *s, int *i, int *nb_lettre);
void					lettre_operator(char const *s, int *i, int *nb_lettre);
int						check_operator(char *s, int *i, unsigned int *nb_word);
int						position_operator(char const *s, int *i, int wn,
						int *iw);

/*
** OTHER:
*/
void					check_opening_quote(char **str);
void					init_ast(char **input, char *s);
char					*missing_quote_prompt(char c);
int						main(int argc, char **argv, char **env);

#endif
