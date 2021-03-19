/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:59:16 by amya              #+#    #+#             */
/*   Updated: 2021/03/15 17:37:13 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	append_space(t_core *core)
{
	char *tmp;

	tmp = core->line;
	core->line = ft_strjoin(core->line, " ");
	free(tmp);
}

void	del_letter(t_core *core)
{
	char	*new;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(core->line);
	if (len % core->term.win.ws_col == 0)
		{
			append_space(core);
			core->space_added = 1;
		}
	if (core->real_pos > ft_strlen(PRE_CMD))
	{
		core->real_pos--;
		if (core->line[core->real_pos] == '\n')
			previous_end_line(core);
		else
			core->pos_h--;
		new = ft_strsub(core->line, 0, core->real_pos);
		tmp = ft_strsub(core->line, core->real_pos + 1,
		len - core->real_pos + 1);
		core->line = ft_strjoin(new, tmp);
	}
	core->del = 0;
	core->move_curs_up = 1;
	print_line(core, 1);
}

void	partial_print_line(t_core *core)
{
	int i;

	i = core->real_pos;
	tputs(tgoto(tgetstr("cm", NULL), core->pos_h, core->pos_v), 0, fd_putchar);
	ft_putstr(tgetstr("cd", NULL));
	while (core->line[i])
	{
		ft_putchar(core->line[i]);
		i++;
	}
}

void	add_letter(t_core *core, char *letter)
{
	char	*start;
	char	*end;

	if (core->real_pos && core->real_pos != ft_strlen(core->line))
	{
		start = ft_strsub(core->line, 0, core->real_pos);
		end = ft_strsub(core->line, core->real_pos, ft_strlen(core->line) - 1);
		free(core->line);
		core->line = ft_strjoin(start, letter);
		free(start);
		start = core->line;
		core->line = ft_strjoin(start, end);
		free(end);
	}
	else
		letter_joining(core, &letter);
	core->real_pos += ft_strlen(letter);
	tab_to_space(core);
	print_line(core, 1);
}

void	cut(t_core *core)
{
	char	*new;

	core->copy = ft_strsub(core->line, core->real_pos,
		(ft_strlen(core->line) - core->real_pos));
	new = ft_strsub(core->line, 0, core->real_pos);
	free(core->line);
	core->line = new;
	core->del = 0;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row && !core->del)
		core->curs_v = core->curs_v - (core->curs_v + core->dl
		+ 1 - core->term.win.ws_row);
	core->del = 1;
	core->nbr_scrolls = 0;
	partial_print_line(core);
}

void	paste(t_core *core)
{
	t_paste	v;

	v.i = 0;
	v.new = ft_strnew(ft_strlen(core->line) + ft_strlen(core->copy));
	while (v.i < core->real_pos)
	{
		v.new[v.i] = core->line[v.i];
		v.i++;
	}
	v.rest = v.i;
	v.j = 0;
	while (core->copy[v.j])
	{
		v.new[v.i] = core->copy[v.j];
		v.i++;
		v.j++;
	}
	while (core->line[v.rest])
	{
		v.new[v.i] = core->line[v.rest];
		v.i++;
		v.rest++;
	}
	free(core->line);
	core->line = v.new;
}

void	copy_paste(t_core *core, int choice)
{
	if (choice == 1)
	{
		if (core->copy)
			free(core->copy);
		core->copy = ft_strsub(core->line, core->real_pos,
		ft_strlen(core->line) - core->real_pos);
	}
	if (choice == 2)
	{
		if (core->copy)
		{
			paste(core);
			core->real_pos += ft_strlen(core->copy);
			core->del = 0;
			core->move_curs_up = 0;
			core->scroll = 1;
		}
	}
	print_line(core, 1);
}
