/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:11:24 by amya              #+#    #+#             */
/*   Updated: 2021/02/28 18:57:37 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	init_core(t_core *core)
{
	core->line = ft_strdup(PRE_CMD);
	core->pos_h = 0;
	core->pos_v = 0;
	core->histo_search = 0;
	core->total_lines =0;
	core->history = NULL;
	core->start = 0;
	core->real_pos = ft_strlen(core->line);
	core->sel = -1;
	core->copy = NULL;
	core->pre_cmd = ft_strlen(core->line);
}

void	read_line_init(t_core *core)
{
	core->scroll = 0;
	g_core = core;
	get_cursor_position(core);
	if (core->line)
	free(core->line);
	if (core->quote)
		core->line = ft_strdup(DQUOTE_CMD);
	else
		core->line = ft_strdup(PRE_CMD);
		core->real_pos = ft_strlen(core->line);
	print_line(core, 1);
	core->nbr_scrolls = 0;
}

int		init_term2(t_core *core)
{
	int				ret;
	t_t				term;
	struct winsize	w;

	tcgetattr(0, &term.config);
	term.config.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &term.config) == -1)
		return (-1);
	if (getenv("TERM") == NULL)
		return (error_manager(0));
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == (-1))
		return (error_manager(1));
	else if (ret == 0)
		return (error_manager(2));
	ioctl(0, TIOCGWINSZ, &w);
	term.win = w;
	core->term = term;
	tputs(tgetstr("ti", NULL), 2, fd_putchar);

	tputs(tgetstr("ve", NULL), 2, fd_putchar);
	return (1);
}