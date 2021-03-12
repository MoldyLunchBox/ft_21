/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:25:00 by amya              #+#    #+#             */
/*   Updated: 2021/03/12 14:51:50 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	search_down(t_core *core)
{
	t_history	*tmp;
	int			i;

	if (core->history)
	{
		i = 0;
		tmp = core->history;
		if (core->histo_search)
			core->histo_search -= 1;
		while (tmp)
		{
			if (i == core->total_lines - core->histo_search)
			{
				histo_found(core, tmp);
				break ;
			}
			i++;
			tmp = tmp->next;
		}
		if (core->histo_search == 0)
			print_line(core, 1);
	}
	else
		print_line(core, 0);
}

void	search_up(t_core *core)
{
	t_history	*tmp;
	int			i;

	if (core->history)
	{
		i = 0;
		tmp = core->history;
		if (core->histo_search < core->total_lines)
			core->histo_search += 1;
		while (tmp)
		{
			if (i == core->total_lines - core->histo_search)
			{
				histo_found(core, tmp);
				break ;
			}
			i++;
			tmp = tmp->next;
		}
	}
	else
	{
		print_line(core, 0);
	}
}

void	history(t_core *core)
{
	core->histo_search = 0;
	core->real_pos = ft_strlen(core->line);
	print_line(core, 1);
	if (core->quote)
	{
		core->history = modify_last_node(core->history, core->line);
	}
	else
	{
		core->total_lines += 1;
		core->history = add_node(core->history, core->line);
	}
}

void	histo_found(t_core *core, t_history *tmp)
{
	core->move_curs_up = 1;
	if (core->histo_search == 0)
	{
		free(core->line);
		if (core->quote)
			core->line = ft_strdup(DQUOTE_CMD);
		else
			core->line = ft_strdup(PRE_CMD);
		core->real_pos = ft_strlen(core->line);
		print_line(core, 1);
	}
	else
	{
		free(core->line);
		core->line = ft_strdup(tmp->line);
		core->real_pos = ft_strlen(core->line);
		core->scroll = 1;
		if (core->curs_v + core->dl + 1 > core->term.win.ws_row)
			core->curs_v = core->curs_v - (core->curs_v +
			core->dl + 1 - core->term.win.ws_row);
		core->nbr_scrolls = 0;
		core->move_curs_up = 1;
		print_line(core, 1);
	}
}

void	max_history(t_core *core)
{
	t_history *tmp;

	tmp = core->history;
	while (tmp->next)
	{
		free(tmp->line);
		tmp->line = ft_strdup(tmp->next->line);
		tmp = tmp->next;
	}
	free(tmp->line);
	tmp->line = ft_strdup(core->line);
	free(core->line);
	core->line = ft_strdup(PRE_CMD);
}
