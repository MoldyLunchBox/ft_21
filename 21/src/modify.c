/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:59:16 by amya              #+#    #+#             */
/*   Updated: 2021/02/28 18:43:14 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	del_letter(t_core *core)
{
	char *new;
	char *tmp;
	int i;
	int len;

	i = 0;
	len = ft_strlen(core->line);
	if (core->real_pos > ft_strlen(PRE_CMD))
	{
		core->real_pos--;
		if (core->line[core->real_pos] == '\n')
			previous_end_line(core);
		else
			core->pos_h--;
		new = ft_strsub(core->line, 0, core->real_pos);
		tmp = ft_strsub(core->line, core->real_pos + 1, len - core->real_pos + 1);
		core->line = ft_strjoin(new, tmp);
	}
	core->del = 0;
	core->move_curs_up = 1;
	print_line(core, 1);
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
	else if (!core->real_pos && ft_strlen(core->line))
	{
		end = core->line;
		core->line = ft_strjoin(letter, core->line);
		free(end);
	}
	else
	{
		end = core->line;
		core->line = ft_strjoin(core->line, letter);
		free(end);
	}
	core->real_pos += ft_strlen(letter);
	tab_to_space(core);
	print_line(core, 1);
}

void	cut(t_core *core)
{
	if (core->sel >= 0)
	{
		if (core->sel >= core->real_pos)
		{
			core->copy = ft_strsub(core->line, core->real_pos, (core->sel - core->real_pos) + 1);
			ft_cut(core, core->real_pos, core->sel);
		}
		else
		{
			core->copy = ft_strsub(core->line, core->sel, (core->real_pos - core->sel + 1));
			ft_cut(core, core->sel, core->real_pos);
			core->real_pos = core->real_pos - (core->real_pos - core->sel);
		}
	}
	core->sel = -1;
	core->del = 0;
	if (core->curs_v + core->dl + 1 > core->term.win.ws_row && !core->del)
		core->curs_v = core->curs_v - (core->curs_v + core->dl + 1 - core->term.win.ws_row);
	core->del = 1;
	core->nbr_scrolls = 0;
	print_line(core, 1);
}

void	paste(t_core *core)
{
	int		i;
	char	*new;
	int		rest;
	int		j;

	i = 0;
	new = ft_strnew(ft_strlen(core->line) + ft_strlen(core->copy));
	while (i < core->real_pos)
	{
		new[i] = core->line[i];
		i++;
	}
	rest = i;
	j = 0;
	while (core->copy[j])
	{
		new[i] = core->copy[j];
		i++;
		j++;
	}
	while (core->line[rest])
	{
		new[i] = core->line[rest];
		i++;
		rest++;
	}
	free(core->line);
	core->line = new;
}

void	copy_paste(t_core *core, int choice)
{
	if (core->sel >= 0 && choice == 1)
	{
		if (core->copy)
			free(core->copy);
		if (core->sel >= core->real_pos)
			core->copy = ft_strsub(core->line, core->real_pos, (core->sel - core->real_pos) + 1);
		else
			core->copy = ft_strsub(core->line, core->sel, (core->real_pos - core->sel) + 1);
	}
	core->sel = -1;
	if (core->sel == -1 && choice == 2)
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

void	ctrl_d2(t_core *core)
{
	char *new;
	char *tmp;
	int i;
	int len;
	int t;

	t = 0;
	i = 0;
	len = ft_strlen(core->line);
	if (core->real_pos > 6 && core->real_pos < len - 1)
	{
		new = ft_strsub(core->line, 0, core->real_pos);
		tmp = ft_strsub(core->line, core->real_pos + 1, len - core->real_pos + 1);
		core->line = ft_strjoin(new, tmp);
		core->del = 0;
		core->move_curs_up = 1;
	}
	core->del = 0;
	core->move_curs_up = 1;
	print_line(core, 1);
}

void	ctrl_d(t_core *core)
{
	if (core->line[core->pre_cmd] == '\0')
		free_to_leave();
}
