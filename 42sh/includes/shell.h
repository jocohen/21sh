/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:01:28 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/12 18:37:41 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
*********************************** INCLUDES ***********************************
*/

# include "../libft/includes/libft.h"

# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>

/*
********************************** STRUCTURES **********************************
*/

typedef struct			s_cursor
{
	size_t				l;
	size_t				c;
}						t_cursor;

typedef struct			s_buf
{
	char				*s;
	size_t				x;
	t_cursor			pos;
	size_t				buf_size;
}						t_buf;

typedef struct			s_historic
{
	char				*origin;
	char				*modif;
	struct s_historic	*next;
	struct s_historic	*prev;
}						t_historic;

typedef struct			s_alloc
{
	t_list				**env;
	t_historic			**history;
	t_buf				*input;
}						t_alloc;

/*
*********************************** GLOBALS ***********************************
*/

int						g_pid;
int						g_resize;
char					*g_clip;

/*
********************************************************************************
******************************** FUNC PROTOTYPES *******************************
********************************************************************************
*/

/*
************************************* ENV **************************************
*/

int						env_to_lst(char **s, t_list **fp);
char					*find_var_value(t_list *fp, char *var);
int						lst_deletion(t_list **fp);
char					*get_end_pwd(char *pwd);

/*
*********************************** PROMPTER ***********************************
*/

void					prompt(t_alloc al);
char					*read_input(t_alloc al);
char					*read_and_sig(t_alloc al, char *k, int stdin_cpy);
char					*kill_or_give(t_alloc al, char k);
char					check_prev_read(char k);
void					check_over_buffer(t_buf *input, char *into_buff);
void					input_character(t_buf *input, char k);
void					check_last_char_column(t_buf *input);
char					*recall_prompt(t_alloc al, int type);
void					analyse_input(t_alloc al, char k);
void					input_visual_char(t_alloc al, char k);
char					*enter_section(t_alloc al, int read);

/*
***************************** EXEC OF SPECIAL KEYS *****************************
*/

void					escape_analysis(t_alloc al);
int						check_wrong_key(char *key);
int						input_keys_def(t_alloc al, char *key);
void					del_char(t_buf *input, int type, t_list **lst);
void					page_move(t_buf *input, char k, t_historic **history,
									t_list **lst);
void					arrow_move(t_buf *input, char k, t_historic **history,
									t_list **lst);
void					home_end_move(t_buf *input, char k);
void					ctrl_arrow_move(t_buf *input, char k);
void					selection_cmd(t_buf *input, char k, t_list **lst);
void					selection_input(t_buf *input, char k, t_list **lst);

/*
************************************ TERMIOS ***********************************
*/

void					set_terminal(t_list *fp, int reset);

/*
*********************************** HISTORIC ***********************************
*/

void					historic_move(t_buf *input, t_historic **history,
										int direction, t_list **lst);
void					move_front_or_back(t_historic **lst, int direction);
void					cmd_spe_search(t_historic **history, t_buf *input,
										int direction, t_list **lst);
void					install_new_line(t_historic **history, t_buf *input,
										t_list **env);
int						search_cmd_common(const char *s, const char *sch);

int						init_hist(t_historic **history, t_list *lst);
int						historic_opening(t_list *lst, int open_type);
void					historic_entry(t_buf *input, t_historic **history,
										int read, t_list *lst);
t_historic				*ft_new_cmd_hist(void);
int						ft_del_hist(t_historic **fp);
void					reset_hist(t_historic *tmp);

/*
************************************ CURSOR ************************************
*/

void					cursor_movement(t_buf *input, int dir);
int						window_width_size(void);
void					check_resize_curs_pos(t_buf *input);
void					vertical_cursor(t_buf *input, int direction);
void					cursor_one_down(t_buf *input);
void					up_into_final_pos(t_buf *input);
void					replace_cursor(t_buf *input, size_t c, size_t l);

/*
*********************************** SELECTION **********************************
*/

t_buf					*selec_buffer(int t, t_buf *input, t_list **lst);
t_buf					*alloc_selec_buff(int dir);
void					selection_init(t_buf *input, int dir, t_list **lst);
void					expand_selec(t_buf *selec, t_buf *input, t_list **lst,
										int dir);
void					paste_intra_clip(t_buf *input, t_list **lst);
void					cut_selection(t_buf *input, t_buf *selec, t_list **lst);

/*
*********************************** DISPLAYS ***********************************
*/

void					caller_display(t_list *fp, t_buf *input,
										int change_pos);
void					fancy_display(char *pwd);
void					classic_display(char *prompt);
void					reactualize_output(t_buf *input, t_list **lst);
int						display_sizing(int size);
void					delete_line_pos(t_buf *input, t_list **lst);
void					display_spe_line(t_buf *selec, t_buf *input);
void					redisplay_line_selec(t_buf *selec, t_buf *input,
											t_list **lst);

/*
*********************************** SIGNALS ************************************
*/

void					sig_kill(int sig);
void					sig_window(int t);
int						quit_signal(char **av);

/*
************************************* MISC *************************************
*/

void					ft_exit(int status);
void					*ft_realloc(void *ptr, size_t size, size_t len);
int						ft_writestdin(int c);

#endif
