/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:13:44 by amya              #+#    #+#             */
/*   Updated: 2021/02/28 18:57:06 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

int		is_a_movement_key(t_core *core, char *fd)
{
	int curs_v;

	curs_v = core->curs_v;
	if(core->curs_v + core->dl + 1 > core->term.win.ws_row)
		curs_v = core->curs_v - (core->curs_v + core->dl + 1 - core->term.win.ws_row);
	
	if ((*((int *)fd) == KEY_DOWN && core->sel < 0) ||
	(*((int *)fd) == KEY_UP && core->sel < 0)
	|| (*((int *)fd) == KEY_LEFT) || (*((int *)fd) == KEY_RIGHT) ||
	(*((int *)fd) == ALT_UP && core->pos_v > curs_v) || (*((int *)fd) == ALT_DOWN))
		return (1);
	return (0);
}

void	movement_key(t_core *core, char *fd)
{
	if (*((int *)fd) == KEY_UP && core->sel < 0)
		search_up(core);
	else if (*((int *)fd) == KEY_DOWN && core->sel < 0)
		search_down(core);
	else if (*((int *)fd) == KEY_LEFT)
		move_curs_left(core);
	else if (*((int *)fd) == KEY_RIGHT)
		move_curs_right(core);
	else if (*((int *)fd) == ALT_UP)
		alt_jump_up(core);
	else if (*((int *)fd) == ALT_DOWN)
		alt_jump_down(core);
}

void	move_curs_left(t_core *core)
{
	int curs_v;

	curs_v = core->curs_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		curs_v = core->curs_v - (core->curs_v + core->dl + 1 - core->term.win.ws_row);
	if (core->real_pos > core->pre_cmd)
	{
		if (core->pos_h > 0)
			core->pos_h -= 1;
		else
			calc_position(core, core->real_pos - 1);
		core->real_pos--;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, curs_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	if (core->sel >= 0)
		selected_print(core);
	else
		ft_putstr(core->line);
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
}

void	move_curs_right(t_core *core)
{
	int curs_v;

	curs_v = core->curs_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		curs_v = core->curs_v - (core->curs_v + core->dl + 1 - core->term.win.ws_row);
	if (core->real_pos < ft_strlen(core->line))
	{
		calc_position(core, core->real_pos + 1);
		core->real_pos++;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, curs_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	if (core->sel >= 0)
		selected_print(core);
	else
		ft_putstr(core->line);
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
}

void	alt_jump_up(t_core *core)
{
	int i;
	int pos_v;
	int len;

	len = 0;
	int curs_v;
	curs_v = core->curs_v;
	if (core->curs_v + core->dl +1 > core->term.win.ws_row  )
		curs_v = core->curs_v - (core->curs_v + core->dl +1 - core->term.win.ws_row);
	pos_v = curs_v;
	i = 0;
	if (core->pos_v)
	{
		core->pos_v--;
		while (core->line[i])
		{
			if (pos_v == core->pos_v && core->pos_h == len)
				break ;
			if ((len && (len + 1) % core->term.win.ws_col == 0) || core->line[i] == '\n')
			{
				if (pos_v == core->pos_v)
					break ;
				pos_v++;
				len = -1;
			}
			len++;
			i++;
		}
	}
	alt_jump_up_print(core, i, len);
}


void	alt_jump_down(t_core *core)
{
	int n;
	int v;
	int line;
	int i = 0;
	int curs_v;

	curs_v = core->curs_v;
	if(core->curs_v + core->dl +1 > core->term.win.ws_row)
		curs_v = core->curs_v - (core->curs_v + core->dl +1 - core->term.win.ws_row);
	v = curs_v;
	n = core->real_pos;
	line = 0;
	while(core->line[i])
	{
		if ((v == core->pos_v+1 && line == core->pos_h) || (v == core->pos_v+1 && core->line[i] == '\n'))
			break ;
		if(core->line[i] == '\n' || (((line + 1) % (core->term.win.ws_col)) == 0 && i))
		 {
			 v++;
			line = -1;
		}
		i++;
		line++;	
	}
	core->pos_h = line;
	core->real_pos = i;
	print_line(core,1);
}