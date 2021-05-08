/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:18:13 by amya              #+#    #+#             */
/*   Updated: 2021/04/25 16:30:38 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	alt_jump_up_print(t_core *core, int position, int len)
{
	if (position < core->pre_cmd)
	{
		core->real_pos = core->pre_cmd;
		calc_position(core, core->pre_cmd);
	}
	else
	{
		core->pos_h = len;
		core->real_pos = position;
	}
	print_line(core, 1);
}

void	delet_space(t_core *core)
{
	core->line[ft_strlen(core->line) - 1] = 0;
	core->space_added = 0;
}

int		calc_curs_v(int curs_v, t_core *core)
{
	int pos_v;
	int test;
	int i;

	i = 0;
	test = 100;
	pos_v = core->pos_v;
	calc_position(core, core->real_pos);
	pos_v = core->pos_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row && !core->del)
	{
		curs_v = core->curs_v - (core->curs_v +
		core->dl + 1 - core->term.win.ws_row);
		test = core->curs_v + core->dl -
		core->term.win.ws_row - core->nbr_scrolls;
		while (i <= test && core->scroll)
		{
			tputs(tgoto(tgetstr("cm", NULL), core->pos_h,
			core->term.win.ws_row - 1), 0, fd_putchar);
			ft_putstr(tgetstr("sf", NULL));
			i++;
			core->nbr_scrolls++;
		}
	}
	return (curs_v);
}


void	debugstr(char *str, int nl)
{
	ft_putstr_fd("|",2);
	ft_putstr_fd(str,2);
	ft_putstr_fd("|",2);
	if (nl)
		ft_putendl_fd("",2);
}

void	debugnbr(int nbr, int nl,int fd)
{
	//ft_putstr_fd(tgetstr("cl", NULL),2);
	ft_putstr_fd("|",fd);
	ft_putnbr_fd(nbr,fd);
	ft_putstr_fd("|",fd);
	if (nl)
		ft_putendl_fd("",fd);
}

void	print_line(t_core *core, int calc_pos)
{
	int curs_v;

	curs_v = core->curs_v;
	if (calc_pos)
		curs_v = calc_curs_v(curs_v, core);
	if (core->out_buf < 0)
		curs_v = -1;
	if (curs_v < 0)
		curs_v = -1;
	tputs(tgoto(tgetstr("cm", NULL), core->curs_h, curs_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	if (curs_v < 0)
		surpassed_screen(core, curs_v);
	ft_putstr(core->line);
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
	if (core->move_curs_up)
	{
		core->curs_v = curs_v;
		core->nbr_scrolls = 0;
	}
	if (core->space_added)
		delet_space(core);
}

int		error_manager(int error)
{
	int ret;

	ret = 1;
	if (error == ERR_NOTERM)
	{
		ft_putstr("TERM must be set (see 'env'). \n");
		exit(1);
	}
	if (error == ERR_TERMDB)
	{
		ft_putstr("Could not access to the termcap database ..\n");
		exit(1);
	}
	if (error == ERR_TNOTF)
	{
		ft_putstr("Terminal type is not defined in termcap database"
		" (or has too few informations). \n");
		exit(1);
	}
	return (ret);
}
