/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:57:04 by amya              #+#    #+#             */
/*   Updated: 2021/03/20 14:52:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"


void		continu(int sig)
{
	(void)sig;
	init_term2(g_core);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTSTP, sig_pause);
	ioctl(2, TIOCSTI, (char[2]){48, 0});
}

void		tests(int sig)
{
	(void)sig;
	print_line(g_core, 1);
	free(g_core->line);
	g_core->line = ft_strdup(PRE_CMD);
	g_core->real_pos = ft_strlen(g_core->line);
	tputs(tgoto(tgetstr("cm", NULL), 0, g_core->curs_v +
	g_core->dl), 0, fd_putchar);
	ft_putstr("\n");
	read_line_init(g_core);
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

void	sig_pause(int sig)
{
	(void)sig;
	unconfigure_term();
	signal(SIGCONT, continu);
	signal(SIGTSTP, SIG_DFL);
	ioctl(2, TIOCSTI, (char[2]){032, 0});
}
