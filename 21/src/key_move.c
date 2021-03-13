/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:13:44 by amya              #+#    #+#             */
/*   Updated: 2021/03/13 12:03:54 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

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
		curs_v = core->curs_v - (core->curs_v + core->dl +
		1 - core->term.win.ws_row);
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
		curs_v = core->curs_v - (core->curs_v + core->dl + 1 -
		core->term.win.ws_row);
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
	t_alt_jump_up	v;

	init_alt_jump_up(&v, core);
	if (core->pos_v)
	{
		core->pos_v--;
		while (core->line[++v.i])
		{
			if (v.pos_v == core->pos_v && core->pos_h == v.len)
				break ;
			if ((v.len && (v.len + 1) % core->term.win.ws_col == 0)
			|| core->line[v.i] == '\n')
			{
				if (v.pos_v == core->pos_v)
					break ;
				v.pos_v++;
				v.len = -1;
			}
			v.len++;
		}
	}
	alt_jump_up_print(core, v.i, v.len);
}

void	alt_jump_down(t_core *core)
{
	t_alt_jump_down	v;

	v.i = -1;
	v.curs_v = core->curs_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		v.curs_v = core->curs_v - (core->curs_v + core->dl
		+ 1 - core->term.win.ws_row);
	init_alt_jump_down(&v, core->real_pos);
	while (core->line[++v.i])
	{
		if ((v.v == core->pos_v + 1 && v.line == core->pos_h)
		|| (v.v == core->pos_v + 1 && core->line[v.i] == '\n'))
			break ;
		if (core->line[v.i] == '\n' || (((v.line + 1) %
		(core->term.win.ws_col)) == 0 && v.i))
		{
			v.v++;
			v.line = -1;
		}
		v.line++;
	}
	core->pos_h = v.line;
	core->real_pos = v.i;
	print_line(core, 1);
}
