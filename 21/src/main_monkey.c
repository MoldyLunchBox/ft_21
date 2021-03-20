/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_monkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:26:13 by amya              #+#    #+#             */
/*   Updated: 2021/03/20 14:54:48 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	unconfigure_term(void)
{
	t_t term;

	tcgetattr(2, &term.config);
	term.config.c_lflag |= (ICANON | ECHO);
	tcsetattr(2, TCSANOW, &term.config);
	tputs(tgetstr("te", NULL), 2, fd_putchar);
	tputs(tgetstr("ve", NULL), 2, fd_putchar);
}

int		enter_exit(t_core *core, char *fd)
{
	if (*((int *)fd) == ESC)
		free_to_leave();
	else if (*((int *)fd) == KEY_ENTER)
	{
		if (str_is_whitespace(core->line + ft_strlen(PRE_CMD), 1))
		{
			if (core->line)
				free(core->line);
			if (core->quote)
				core->line = ft_strdup(DQUOTE_CMD);
			else
				core->line = ft_strdup(PRE_CMD);
			print_line(core, 1);
			return (0);
		}
		else
		{
			history(core);
			return (1);
		}
	}
	return (0);
}

void	real_line_add_letter(t_core *core, char *fd)
{
	core->del = 0;
	core->move_curs_up = 0;
	core->scroll = 1;
	add_letter(core, fd);
	ft_bzero(fd, 4);
}

char	*readline(t_core *core)
{
	char	fd[5];

	read_line_init(core);
	while (1)
	{
		readline_loop_init(fd, core);
		while (read(0, fd, 4) > 0 && is_not_button(fd))
			real_line_add_letter(core, fd);
		if ((is_a_movement_key(core, fd)))
			movement_key(core, fd);
		else if (is_an_editing_key(core, fd))
			editing_keys(core, fd);
		else if (is_enter_exit_key(core, fd))
		{
			if (enter_exit(core, fd))
				return (ft_strsub(core->line, ft_strlen(PRE_CMD),
				ft_strlen(core->line) - ft_strlen(PRE_CMD)));
			else
				return (NULL);
		}
		else
			print_line(core, 1);
	}
	return (ft_strsub(core->line, ft_strlen(PRE_CMD),
	ft_strlen(core->line) - ft_strlen(PRE_CMD)));
}

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

int		main(int ac, char **ar)
{
	t_core	core;
	int		i;
	char	*line;
	char	*temp;
	char	*tmp;

	i = 0;
	catch_signal();
	init_term2(&core);
	init_core(&core);
	core.quote = 0;
	ft_putstr(tgetstr("cl", NULL));
	while (1)
	{
		line = readline(&core);
		ft_putendl("");
		while ((i = check_quotes(line)))
		{
			temp = ft_strjoin(line, "\n");
			ft_strdel(&line);
			tmp = readline(&core);
			ft_putchar('\n');
			if (!tmp)
				tmp = ft_strdup("");
			line = ft_strjoin(temp, tmp);
			ft_strdel(&temp);
			ft_strdel(&tmp);
		}
	}
}
