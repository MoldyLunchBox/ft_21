/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_rest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:51:09 by amya              #+#    #+#             */
/*   Updated: 2021/01/04 16:51:10 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

int		is_an_editing_key(t_core *core, char *fd)
{
	if ((*((int *)fd) == SELECT) || *((int *)fd) == CTRL_D ||	(*((int *)fd) == COPY) ||
	 (*((int *)fd) == CUT) || (*((int *)fd) == KEY_DEL && core->sel < 0) ||
	 (*((int *)fd) == PASTE))
	 return (1);
	return (0);
}

int		is_enter_exit_key(t_core *core, char *fd)
{
	if ((*((int *)fd) == ESC) || (*((int *)fd) == KEY_ENTER && core->sel < 0))
		return (1);
	return (0);
}
