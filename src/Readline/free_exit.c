/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:57:57 by amya              #+#    #+#             */
/*   Updated: 2021/03/21 16:54:51 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	free_struct(t_history *core)
{
	t_history *tmp;

	while (core)
	{
		tmp = core;
		if (core->line)
			free(core->line);
		core = core->next;
		free(tmp);
	}
}

void	free_to_leave(void)
{
	unconfigure_term();
	if (g_core->line)
		free(g_core->line);
	if (g_core->copy)
		free(g_core->copy);
	if (g_core->history)
		free_struct(g_core->history);
	exit(0);
}

void	unconfigure_term(void)
{
	t_te	term;

	tcgetattr(2, &term.config);
	term.config.c_lflag |= (ICANON | ECHO);
	tcsetattr(2, TCSANOW, &term.config);
	tputs(tgetstr("ve", NULL), 2, fd_putchar);
}

void	make_line(t_core *core, int len)
{
	char	*new;
	char	*tmp;
	char	*ptr;

	ptr = core->line;
	new = ft_strsub(core->line, 0, core->real_pos);
	tmp = ft_strsub(core->line, core->real_pos + 1,
	len - core->real_pos + 1);
	core->line = ft_strjoin(new, tmp);
	free(ptr);
	free(new);
	free(tmp);
}
