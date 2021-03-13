/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monkey_head.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 14:20:36 by amya              #+#    #+#             */
/*   Updated: 2021/03/13 18:50:25 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONKEY_HEAD_H
# define MONKEY_HEAD_H
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# define CANONIC_MODE 536872399;
# define NON_CANONIC_MODE 536872143;
#define KEY_UP 4283163 
#define KEY_DOWN 4348699
#define KEY_LEFT 4479771
#define KEY_RIGHT 4414235
#define KEY_DEL 2117294875
#define KEY_ENTER 10
#define KEY_BACKSPACE 127
#define ESC 27
#define EXIT 45
#define SELECT 5263131
#define COPY 5328667
#define PASTE 5394203
#define CUT 5459739
#define ALT_UP 41410
#define ALT_DOWN 10650850
#define PRE_CMD    "user%%: "
#define SQUOTE_CMD "squote: "
#define DQUOTE_CMD "dquote: "
#define CTRL_D 4
#define RESET "\033[00m"
#define FD 2
# define RESET "\033[00m"
# define RED "\033[31m"


enum
{
        ERR_NOTERM,
        ERR_TERMDB,
        ERR_TNOTF,
        ERR_USAGE,
};
typedef struct	s_t
{
	struct winsize win;
	struct termios config;
}				t_t;

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
}				t_history;


typedef	struct	s_core
{
	char	*line;
	//char	*buff;
	t_history *history;
	int		curs_h;
	int		curs_v;
	int		dl; // total displayed lines
	int		total_lines; //total history lines
	int		pos_end_h;
	int		scroll;
	int 	nbr_scrolls;
	int		histo_search;
	int		move_curs_up;
	int		del;
	char	*copy;
	int		var;
	int		pre_cmd;
	int		sel;
	int		start;
	int		pos_h;
	int		pos_v;
	int		real_pos;
	t_t		term;
	int		index;
	int		needed_rows;
	int		quote;
	int		argc;
	int		fit;
}				t_core;
typedef struct	s_alt_jump_down
{
	int n;
	int v;
	int line;
	int i;
	int curs_v;
}				t_alt_jump_down;

typedef struct	s_alt_jump_up
{
	int i;
	int pos_v;
	int len;
	int curs_v;
}				t_alt_jump_up;

typedef struct	s_paste
{
	int		i;
	char	*new;
	int		rest;
	int		j;
}				t_paste;

typedef struct	s_readline
{
	char	fd[5];
	int		buf;
}				t_readline;

t_core			*g_core;
void	print_line(t_core *core, int calc_pos);
t_history			*add_node(t_history *head, char *line);
int				fd_putchar(int c);
int				error_manager(int error);
int				init_term(t_core *core);
void			free_struct(t_history *core);
void			free_to_leave(void);
void			init_core(t_core *core);
void			sprinkle_spaces(int i, t_core *core, int curr_len);
void			show_selected(t_core *core);

void			movement(t_core *core, int buf);
void			delet_item(t_core *core);
void			key_hook(t_core *core);
void			signal_winch(int sig);
void			continu(int sig);
void			unconfigure_term();
void			catch_signal();
void			sig_pause(int sig);
void			stop(int sig);
void			start_or_end(t_core *core, int buf);
void			free_runner(t_history *runner);
void			buttons(t_core *core, int buf);
int		init_term2(t_core *core);
void	add_letter(t_core *core, char *letter);
void	del_letter(t_core *core);
void	aadd_letter(char **string, char *letter, int position);
void history(t_core *core);
//move
int		is_a_movement_key(t_core *core, char *fd);
void	movement_key(t_core *core, char *fd);
void	move_curs_left(t_core *core);
void	move_curs_right(t_core *core);
void	alt_jump_up(t_core *core);

void	alt_jump_down(t_core *core);

void	selected_print(t_core *core);
//history
void	search_down(t_core *core);
void	histo_found(t_core *core, t_history *tmp);
void	history(t_core *core);
void	search_up(t_core *core);
void	max_history(t_core *core);

//init
void	init_core(t_core *core);
void	read_line_init(t_core *core);
int		init_term2(t_core *core);
//print
void	read_line_else_print_line(t_core *core);
void	selected_print(t_core *core);
void	alt_jump_up_print(t_core *core, int position, int len);
void	print_line(t_core *core, int calc_pos);
//calcul
void	calc_displayed_lines(t_core *core );
void	calc_position(t_core *core, int cmd_len);
void	tab_to_space(t_core *core);
void	get_cursor_position(t_core *core);
void	previous_end_line(t_core *core);
//modify
void	add_letter(t_core *core, char *letter);
void	del_letter(t_core *core);
void	paste(t_core *core);
void	copy_paste(t_core *core, int choice);
void	ctrl_d(t_core *core);
//debug
//conditions
int		is_printable(char *fd);
int		ft_iswhitespace(int c, int include_space);
int		str_is_whitespace(char *str, int include_space);
int		is_not_button(char *fd);
 void	editing_keys(t_core *core, char *fd);
 t_history	*modify_last_node(t_history *head, char *line);
 //confitions2
int		is_an_editing_key(t_core *core, char *fd);
int		is_enter_exit_key(t_core *core, char *fd);
int		ft_strsearch(char const *s1, char const *s2);
void	cut(t_core *core);
void	ft_cut(t_core *core, int start, int end);
int		ft_putchar_int(int c);
void	init_alt_jump_down(t_alt_jump_down *v, int real_pos);
void	init_alt_jump_up(t_alt_jump_up *v, t_core *core);
void	letter_joining(t_core *core, char **letter);
void	readline_loop_init(char *fd, t_core *core);
void	ctrl_d2(t_core *core);
void	debugstr(char *str, int nl);

#endif
