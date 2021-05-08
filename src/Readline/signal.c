/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:57:04 by amya              #+#    #+#             */
/*   Updated: 2021/03/24 13:51:00 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	tests(int sig)
{
	(void)sig;

	g_core->real_pos = ft_strlen(g_core->line);
	calc_position(g_core, g_core->real_pos);
	tputs(tgoto(tgetstr("cm", NULL), g_core->pos_h,
	g_core->pos_v), 0, fd_putchar);
	g_core->curs_v = g_core->pos_v;
	free(g_core->line);
	g_core->line = ft_strdup(PRE_CMD);
	g_core->real_pos = ft_strlen(g_core->line);
	if (g_core->curs_v < g_core->term.win.ws_row - 1)
		g_core->curs_v++;
	ft_putstr("\n");
	g_core->curs_h = 0;
	g_core->quote = 0;
	g_core->heredoc = 0;
	read_line_init(g_core, 0);
}

void	stop(int sig)
{
	(void)sig;
}

void	catch_signal(void)
{
	int i;

	i = 0;
	signal(SIGINT, tests);
}
