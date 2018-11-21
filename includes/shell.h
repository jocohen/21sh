/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:01:28 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/15 16:59:00 by jocohen          ###   ########.fr       */
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

int				g_pid;
int				g_resize;

int				env_to_lst(char **s, t_list **fp);
char			*find_var_value(t_list *fp, char *var);
void			ft_exit(int status);
void			set_terminal(t_list *fp, int reset);
void			prompt(t_list **lst, t_historic **history);
void			*ft_realloc(void *ptr, size_t size, size_t len);
void			caller_display(t_list *fp, t_buf *input);
void			escape_analysis(t_buf *input, t_historic **history);
void			del_char(t_buf *input, int type);
int				ft_writestdin(int c);
int				lst_deletion(t_list **fp);
char			*get_end_pwd(char *pwd);
void			enter_section(t_buf *input, t_list **lst, t_historic **history, int read);
void			sig_c(int sig);
int				quit_signal(char **av);
int				init_hist(t_historic **history, t_list *lst);
void			historic_move(t_buf *input, t_historic **history, int direction);
char			check_prev_read(char k);
int				ft_del_hist(t_historic **fp);
void			reset_hist(t_historic *tmp);
t_historic		*ft_new_cmd_hist(void);
void			check_over_buffer(t_buf *input, char *into_buff);
int				display_sizing(int size);
void			cursor_movement(t_buf *input, int dir);
int				window_width_size(void);
int				window_line_size(void);
void			sig_window(int t);
void			check_resize_curs_pos(t_buf *input);
void			delete_line_pos(t_buf *input);
void			vertical_cursor(t_buf *input, int direction);

#endif
