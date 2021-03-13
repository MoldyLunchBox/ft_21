/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:06:41 by amya              #+#    #+#             */
/*   Updated: 2021/03/13 12:24:12 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

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
	int		i;
	int		len;
	int		t;

	t = 0;
	i = 0;
	len = ft_strlen(core->line);
	if (core->real_pos > 6 && core->real_pos < len - 1)
	{
		new = ft_strsub(core->line, 0, core->real_pos);
		tmp = ft_strsub(core->line, core->real_pos +
		1, len - core->real_pos + 1);
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

