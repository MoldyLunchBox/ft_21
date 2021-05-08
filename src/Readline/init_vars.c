/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:50:01 by amya              #+#    #+#             */
/*   Updated: 2021/03/20 15:51:54 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	init_alt_jump_down(t_alt_jump_down *v, int real_pos)
{
	v->v = v->curs_v;
	v->n = real_pos;
	v->line = 0;
}

void	init_alt_jump_up(t_alt_jump_up *v, t_core *core)
{
	v->len = 0;
	v->curs_v = core->curs_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		v->curs_v = core->curs_v - (core->curs_v + core->dl
		+ 1 - core->term.win.ws_row);
	v->pos_v = v->curs_v;
	v->i = -1;
}

void	readline_loop_init(char *fd, t_core *core)
{
	core->move_curs_up = 0;
	ft_bzero(fd, 5);
}
