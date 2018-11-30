/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:01:28 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/30 16:12:08 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/includes/libft.h"

# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct	s_cursor
{
	size_t		l;
	size_t		c;
}				t_cursor;

typedef struct	s_buf
{
	char		*s;
	size_t		x;
	t_cursor	pos;
	size_t		buf_size;
}				t_buf;

typedef struct			s_historic
{
	char				*origin;
	char				*modif;
	struct s_historic	*next;
	struct s_historic	*prev;
}						t_historic;

typedef struct	s_prompt
{
	char		*input;
	t_list		**lst;
	t_historic	**hist;
}				t_prompt;

int				g_pid;
int				g_resize;
char			*g_clip;

int				env_to_lst(char **s, t_list **fp);
char			*find_var_value(t_list *fp, char *var);
void			ft_exit(int status);
void			set_terminal(t_list *fp, int reset);
char			*prompt(t_list **lst, t_historic **history);
void			*ft_realloc(void *ptr, size_t size, size_t len);
void			caller_display(t_list *fp, t_buf *input, int change_pos);
void			escape_analysis(t_buf *input, t_historic **history, t_list **lst);
void			del_char(t_buf *input, int type, t_list **lst);
int				ft_writestdin(int c);
int				lst_deletion(t_list **fp);
char			*get_end_pwd(char *pwd);
char			*enter_section(t_buf *input, t_list **lst, t_historic **history, int read);
void			sig_c(int sig);
int				quit_signal(char **av);
int				init_hist(t_historic **history, t_list *lst);
void			historic_move(t_buf *input, t_historic **history, int direction, t_list **lst);
char			check_prev_read(char k);
int				ft_del_hist(t_historic **fp);
void			reset_hist(t_historic *tmp);
t_historic		*ft_new_cmd_hist(void);
void			check_over_buffer(t_buf *input, char *into_buff);
int				display_sizing(int size);
void			cursor_movement(t_buf *input, int dir);
int				window_width_size(void);
void			sig_window(int t);
void			check_resize_curs_pos(t_buf *input);
void			delete_line_pos(t_buf *input, t_list **lst);
void			vertical_cursor(t_buf *input, int direction);
t_buf			*selec_buffer(int t, t_buf *input, t_list **lst);
void			replace_cursor(t_buf *input, size_t c, size_t l);
void			reactualize_output(t_buf *input, t_list **lst);
void			selection_init(t_buf *input, int dir, t_list **lst);
void			input_character(t_buf *input, char k);
void			check_last_char_column(t_buf *input);
void			paste_intra_clip(t_buf *input, t_list **lst);
void			cut_selection(t_buf *input, t_buf *selec, t_list **lst);
int				historic_opening(t_list *lst, int open_type);
char			*recall_prompt(t_list **lst, t_historic **history, int type);

#endif
