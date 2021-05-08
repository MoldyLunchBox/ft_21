/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_rest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:51:09 by amya              #+#    #+#             */
/*   Updated: 2021/03/22 17:56:05 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

int		is_an_editing_key(char *fd)
{
	if (*((int *)fd) == CTRL_D ||
	(*((int *)fd) == COPY) ||
	(*((int *)fd) == CUT) || (*((int *)fd) == KEY_DEL) ||
	(*((int *)fd) == PASTE))
		return (1);
	return (0);
}

int		is_enter_exit_key(char *fd)
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
	(*((int *)fd) == KEY_DOWN) || (*((int *)fd) == W_LEFT) ||
	(*((int *)fd) == KEY_UP) || (*((int *)fd) == W_RIGHT)
	|| (*((int *)fd) == KEY_LEFT) || (*((int *)fd) == KEY_RIGHT) ||
	(*((int *)fd) == ALT_UP && core->pos_v > curs_v)
	|| (*((int *)fd) == ALT_DOWN))
		return (1);
	return (0);
}
