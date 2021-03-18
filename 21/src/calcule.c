/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:53:43 by amya              #+#    #+#             */
/*   Updated: 2021/03/16 15:16:15 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	calc_displayed_lines(t_core *core)
{
	int i;
	int new_line;

	new_line = 0;
	i = 0;
	core->dl = 0;
	while (core->line[i])
	{
		if (core->line[i] == '\n' || (((new_line + 1) %
		(core->term.win.ws_col)) == 0 && i))
		{
			core->dl++;
			new_line = -1;
		}
		i++;
		new_line++;
	}
}

void	calc_position(t_core *core, int cmd_len)
{
	int	new_line;
	int	check;
	int	i;

	i = 0;
	new_line = 0;
	debugnbr(core->curs_v,1,2);
	
	calc_displayed_lines(core);
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		core->pos_v = core->curs_v - (core->curs_v + core->dl +
		1 - core->term.win.ws_row);
	else
		core->pos_v = core->curs_v;
	while (core->line[i] && i < cmd_len)
	{
		if (core->line[i] == '\n' || (((new_line + 1) %
		(core->term.win.ws_col)) == 0 && i))
		{
			core->pos_v++;
			new_line = -1;
		}
		i++;
		new_line++;
	}
	core->pos_h = new_line;
	debugnbr(core->curs_v,1,2);

}

void	tab_to_space(t_core *core)
{
	int i;

	i = 0;
	while (core->line[i])
	{
		if (core->line[i] == '\t')
			core->line[i] = ' ';
		i++;
	}
}

void	get_cursor_position(t_core *core)
{
	int		column;
	int		row;
	char	buf;

	column = 0;
	row = 0;
	tputs("\e[6n", 0, ft_putchar_int);
	while (read(0, &buf, 1) > 0 && buf != '[')
		;
	while (read(0, &buf, 1) > 0 && buf != ';')
		if (ft_isdigit(buf))
			row = (row * 10) + (buf - '0');
	while (read(0, &buf, 1) > 0 && buf != 'R')
		if (ft_isdigit(buf))
			column = (column * 10) + (buf - '0');
	core->curs_v = row - 1;
	core->curs_h = column - 1;
}

void	previous_end_line(t_core *core)
{
	int i;
	int line;
	int length;

	line = 0;
	i = 0;
	length = 0;
	core->pos_v -= 1;
	while (core->line[i])
	{
		if (core->line[i] == '\n')
		{
			if (core->pos_v == line)
				break ;
			line += 1;
			length = -1;
		}
		i++;
		length++;
	}
	core->pos_h = length;
}
