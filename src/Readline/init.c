/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:11:24 by amya              #+#    #+#             */
/*   Updated: 2021/05/08 16:35:28 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	init_core(t_core *core)
{
	core->quote = 0;
	core->line = ft_strdup(PRE_CMD);
	core->pos_h = 0;
	core->pos_v = 0;
	core->histo_search = 0;
	core->total_lines = 0;
	core->history = NULL;
	core->start = 0;
	core->real_pos = ft_strlen(core->line);
	core->copy = NULL;
	core->pre_cmd = ft_strlen(core->line);
	core->opps = (char **)malloc(sizeof(char *) * 11);
	core->opps[0] = ft_strdup(">");
	core->opps[1] = ft_strdup("&>");
	core->opps[2] = ft_strdup(">>");
	core->opps[3] = ft_strdup("&>>");
	core->opps[4] = ft_strdup("<");
	core->opps[5] = ft_strdup("<<");
	core->opps[6] = ft_strdup(">&");
	core->opps[7] = ft_strdup("<&");
	core->opps[8] = ft_strdup(">&-");
	core->opps[9] = ft_strdup("<&-");
	core->opps[10] = NULL;
	g_core = core;

}

void	read_line_init(t_core *core, int calc_pos)
{
	core->scroll = 0;
	core->space_added = 0;
	core->out_buf = 0;
	if (calc_pos)
		get_cursor_position(core);
	core->pos_v = core->curs_v;
	if (core->line)
		free(core->line);
	if (core->quote)
		core->line = ft_strdup(DQUOTE_CMD);
	else if (core->heredoc)
		core->line = ft_strdup(HERDC_CMD);
	else
		core->line = ft_strdup(PRE_CMD);
	core->real_pos = ft_strlen(core->line);
	if (g_checker == 0)
		print_line(core, 1);
	core->nbr_scrolls = 0;
}

int		init_term2(t_core *core)
{
	int				ret;
	t_te			term;
	struct winsize	w;

	tcgetattr(0, &term.config);
	term.config.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &term.config) == -1)
		return (-1);
	// if (!ft_strequ(getenv("TERM"), "xterm-256color"))
	// 	return (error_manager(0));
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == (-1))
		return (error_manager(1));
	else if (ret == 0)
		return (error_manager(2));
	ioctl(0, TIOCGWINSZ, &w);
	term.win = w;
	core->term = term;
	tputs(tgetstr("ve", NULL), 2, fd_putchar);
	return (1);
}
