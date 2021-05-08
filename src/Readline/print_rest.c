/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:57:43 by amya              #+#    #+#             */
/*   Updated: 2021/03/21 16:10:16 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	partial_print_line(t_core *core)
{
	int i;

	i = core->real_pos;
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	while (core->line[i])
	{
		ft_putchar(core->line[i]);
		i++;
	}
}

int		fd_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int		ft_putchar_int(int c)
{
	ft_putchar((char)c);
	return (0);
}

void	surpassed_screen(t_core *core, int curs_v)
{
	core->del = 0;
	core->move_curs_up = 1;
	core->out_buf = curs_v;
	if (core->dl + 1 <= core->term.win.ws_row)
		core->pos_v++;
}
