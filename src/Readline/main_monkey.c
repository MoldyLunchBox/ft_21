/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_monkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:26:13 by amya              #+#    #+#             */
/*   Updated: 2021/05/09 12:21:44 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

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
			else if (core->heredoc)
				core->line = ft_strdup(HERDC_CMD);
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

	read_line_init(core, 1);
	while (1)
	{
		readline_loop_init(fd, core);
		while (read(0, fd, 4) > 0 && is_not_button(fd))
			real_line_add_letter(core, fd);
		if ((is_a_movement_key(core, fd)))
			movement_key(core, fd);
		else if (is_an_editing_key(fd))
			editing_keys(core, fd);
		else if (is_enter_exit_key(fd))
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



void	do_quotes(char **line, t_core *core)
{
	char	*temp;
	char	*tmp;

	temp = ft_strjoin(*line, "\n");
	ft_strdel(line);
	init_term2(core);
	tmp = readline(core);

	unconfigure_term();
		ft_putchar('\n');
	if (core->quote)
	{
		if (!tmp)
			tmp = ft_strdup("");
		*line = ft_strjoin(temp, tmp);
		ft_strdel(&temp);
		ft_strdel(&tmp);
	}
	else 
		*line = tmp;
}

int		main(int ac, char **ar, char **env)
{
	t_core	core;
	int		i;
	char	*line;
	// t_t		*t_env;

	catch_signal();
	init_core(&core);
	// t_env = init_env(env);
	// while (21)
	// {
	// 	g_checker = 0;
	// 	core.heredoc = 0;
	// 	init_term2(&core);
	// 	line = readline(&core);
	// 	ft_putendl("");
	// 	unconfigure_term();
	// 	while (check_quotes(line))
	// 		do_quotes(&line, &core);
		execution("one | two.4- & > two.6| and  \">\">   4 454 not");
		// if ((i = tosh(&line, &t_env, &ac, &ar)) == -1)
		// 	continue ;
		// else if (i == 0)
		// 	break ;
	// }
	// free_env(&t_env);
	return (0);
}
