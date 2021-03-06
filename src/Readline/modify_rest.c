/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:06:41 by amya              #+#    #+#             */
/*   Updated: 2021/03/25 15:30:21 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	letter_joining(t_core *core, char **letter)
{
	char	*tmp;

	if (!core->real_pos && ft_strlen(core->line))
	{
		tmp = core->line;
		core->line = ft_strjoin(*letter, core->line);
		free(tmp);
	}
	else
	{
		tmp = core->line;
		core->line = ft_strjoin(core->line, *letter);
		free(tmp);
	}
}

void	ctrl_d2(t_core *core)
{
	char	*new;
	char	*tmp;
	char	*fre;
	int		len;

	len = ft_strlen(core->line);
	if (core->real_pos > core->pre_cmd - 1  && core->real_pos < len)
	{
		new = ft_strsub(core->line, 0, core->real_pos);
		tmp = ft_strsub(core->line, core->real_pos +
		1, len - core->real_pos + 1);
		fre = core->line;
		core->line = ft_strjoin(new, tmp);
		free(fre);
		free(new);
		free(tmp);
		core->del = 0;
		core->move_curs_up = 1;
	}
	else if (core->pre_cmd == len && core->heredoc != 1 && core->quote == 0)
		free_to_leave();
	else if (core->heredoc && len == core->pre_cmd)
		core->heredoc = 0;
	else if (core->quote && len == core->pre_cmd)
		{core->quote = 0;
		ft_putendl("");
		read_line_init(g_core, 0);
		}
		
	core->del = 0;
	core->move_curs_up = 1;
	print_line(core, 1);
}

void	go_home(t_core *core)
{
	core->real_pos = core->pre_cmd;
	print_line(core, 1);
}

void	go_to_end(t_core *core)
{
	core->real_pos = ft_strlen(core->line);
	print_line(core, 1);
}

void	append_space(t_core *core)
{
	char *tmp;

	tmp = core->line;
	core->line = ft_strjoin(core->line, " ");
	free(tmp);
}
