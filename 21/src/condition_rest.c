/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_rest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:51:09 by amya              #+#    #+#             */
/*   Updated: 2021/03/19 19:53:02 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

int		is_an_editing_key(t_core *core, char *fd)
{
	if (*((int *)fd) == CTRL_D ||
	(*((int *)fd) == COPY) ||
	(*((int *)fd) == CUT) || (*((int *)fd) == KEY_DEL) ||
	(*((int *)fd) == PASTE))
		return (1);
	return (0);
}

int		is_enter_exit_key(t_core *core, char *fd)
{
	if ((*((int *)fd) == ESC) || (*((int *)fd) == KEY_ENTER))
		return (1);
	return (0);
}

int		is_a_movement_key(t_core *core, char *fd)
{
	int curs_v;

	curs_v = core->curs_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		curs_v = core->curs_v - (core->curs_v + core->dl
		+ 1 - core->term.win.ws_row);
	if ((*((int *)fd) == HOME) || (*((int *)fd) == END) ||
	(*((int *)fd) == KEY_DOWN) ||
	(*((int *)fd) == KEY_UP)
	|| (*((int *)fd) == KEY_LEFT) || (*((int *)fd) == KEY_RIGHT) ||
	(*((int *)fd) == ALT_UP && core->pos_v > curs_v)
	|| (*((int *)fd) == ALT_DOWN))
		return (1);
	return (0);
}
