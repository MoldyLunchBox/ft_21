/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:18:13 by amya              #+#    #+#             */
/*   Updated: 2021/03/17 15:20:29 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	read_line_else_print_line(t_core *core)
{
	if (core->sel >= 0)
		selected_print(core);
	else
		print_line(core, 1);
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

void	selected_print(t_core *core)
{
	int i;
	int curs_v;

	curs_v = core->curs_v;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
		curs_v = core->curs_v - (core->curs_v + core->dl +
		1 - core->term.win.ws_row);
	tputs(tgoto(tgetstr("cm", NULL), 0, curs_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	if (curs_v < 0)
		ft_putendl("");
	i = 0;
	while (core->line[i])
	{
		if ((i >= core->sel && i <= core->real_pos) ||
		(i < core->sel && i > core->real_pos))
			ft_putstr("\033[7m");
		else
			ft_putstr(RESET);
		ft_putchar(core->line[i]);
		i++;
	}
	ft_putstr(RESET);
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
}

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
	if (core->sel >= 0)
		selected_print(core);
	else
	{
		print_line(core, 1);
	}
}

void	delet_space(t_core *core)
{
	core->line[ft_strlen(core->line) - 1] = 0;
	core->space_added = 0;
}

void	print_line(t_core *core, int calc_pos)
{
	int curs_v;
	int pos_v;
	int i;
	int test;

	i = 0;
	test = 100;
	pos_v = core->pos_v;
	curs_v = core->curs_v;
	debugnbr(core->curs_v, 1, 2);
	if (calc_pos)
	{
		calc_position(core, core->real_pos);
		pos_v = core->pos_v;
		if (core->curs_v + core->dl + 1 > core->term.win.ws_row && !core->del)
		{
				debugstr("------------------->",1);
			curs_v = core->curs_v - (core->curs_v + core->dl + 1 - core->term.win.ws_row);
			test = core->curs_v + core->dl - core->term.win.ws_row - core->nbr_scrolls;
			while (i <= test && core->scroll)
			{
				tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->term.win.ws_row - 1), 0, fd_putchar);
				ft_putstr(tgetstr("sf", NULL));
				i++;
				core->nbr_scrolls++;
			}
		}
	}
	debugnbr(core->curs_v, 1, 2);

	debugnbr(curs_v,1,2);

	if (core->out_buf < 0)
		curs_v = -1;
	if (curs_v < 0)
		curs_v = -1;
	tputs(tgoto(tgetstr("cm", NULL), 0, curs_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	if (curs_v < 0)
	{
		core->del = 0;
	core->move_curs_up = 1;
		core->out_buf = curs_v;
		if (core->dl+1 <= core->term.win.ws_row)
		core->pos_v++;
	}
	ft_putstr(core->line);
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
	// debugstr("<", 1);
	if (core->move_curs_up)
	{
		core->curs_v = curs_v;
		core->nbr_scrolls = 0;
	}
	if (core->space_added)
		delet_space(core);
	debugnbr(core->curs_v, 1, 2);
	debugstr("ow", 1);
}


int		error_manager(int error)
{
	int ret;

	ret = 1;
	if (error == ERR_NOTERM)
	{
		ft_putstr("TERM must be set (see 'env'). \n");
		return (-1);
	}
	if (error == ERR_TERMDB)
	{
		ft_putstr("Could not access to the termcap database ..\n");
		return (-1);
	}
	if (error == ERR_TNOTF)
	{
		ft_putstr("Terminal type is not defined in termcap database"
		" (or has too few informations). \n");
		return (-1);
	}
	if (error == ERR_USAGE)
	{
		ft_putstr("ft_select: usage: ./ft_select [arg1] [arg2] ...\n");
		return (-1);
	}
	return (ret);
}

int		fd_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}
