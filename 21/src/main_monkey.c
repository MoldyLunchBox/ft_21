/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_monkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:26:13 by amya              #+#    #+#             */
/*   Updated: 2021/03/13 17:40:41 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	ft_cut(t_core *core, int start, int end)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = ft_strnew(ft_strlen(core->line) - (end - start));
	while (core->line[i] && i < start)
	{
		new[i] = core->line[i];
		i++;
	}
	j = i;
	i = end;
	while (core->line[i])
	{
		new[j] = core->line[i + 1];
		j++;
		i++;
	}
	free(core->line);
	core->line = new;
}

int		ft_putchar_int(int c)
{
	ft_putchar((char)c);
	return (0);
}

void	unconfigure_term(void)
{
	t_t term;

	tcgetattr(2, &term.config);
	term.config.c_lflag |= (ICANON | ECHO);
	tcsetattr(2, TCSANOW, &term.config);
	tputs(tgetstr("te", NULL), 2, fd_putchar);
	tputs(tgetstr("ve", NULL), 2, fd_putchar);
}

int	enter_exit(t_core *core, char *fd)
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
		while (read(0, fd, 4) > 0 && is_not_button(fd) && core->sel < 0)
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
			read_line_else_print_line(core);
	}
	return (ft_strsub(core->line, ft_strlen(PRE_CMD),
	ft_strlen(core->line) - ft_strlen(PRE_CMD)));
}

void		free_struct(t_history *core)
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
		free(g_core->line);
	if (g_core->history)
		free_struct(g_core->history);
	exit(0);
}

void	sig_pause(int sig)
{
	(void)sig;
	unconfigure_term();
	signal(SIGCONT, continu);
	signal(SIGTSTP, SIG_DFL);
	ioctl(2, TIOCSTI, (char[2]){032, 0});
}

void		continu(int sig)
{
	(void)sig;
	init_term2(g_core);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTSTP, sig_pause);
	ioctl(2, TIOCSTI, (char[2]){48, 0});
}

void		tests(int sig)
{
	(void)sig;
	print_line(g_core, 1);
	free(g_core->line);
	g_core->line = ft_strdup(PRE_CMD);
	g_core->real_pos = ft_strlen(g_core->line);
	tputs(tgoto(tgetstr("cm", NULL), 0, g_core->curs_v +
	g_core->dl), 0, fd_putchar);
	ft_putstr("\n");
	read_line_init(g_core);
}

void	stop(int sig)
{
	(void)sig;
}

void	catch_signal(void)
{
	int i;

	i = 0;
	signal(SIGINT, tests);
}

int		ft_strsearch(char const *s1, char const *s2)
{
	int	i;
	int j;

	if (s1 != NULL && s2 != NULL)
	{
		i = 0;
		while (s1[i])
		{
			j = 0;
			while (s1[i] == s2[j] && s1[i] && s2[j])
			{
				i++;
				j++;
			}
			if (!s2[j])
				return (1);
			i++;
		}
	}
	ft_putstr_fd(s1, 2);
	return (0);
}

void	handle_quotes(char c, int *balance)
{
	if (c == '\"' && *balance == 0)
		*balance = 2;
	else if (c == '\'' && *balance == 0)
		*balance = 1;
	else if (c == '\"' && *balance == 2)
		*balance = 0;
	else if (c == '\'' && *balance == 1)
		*balance = 0;
}

int		check_quotes(char *str)
{
	int	i;
	int	balance;

	i = 0;
	balance = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quotes(str[i], &balance);
		i++;
	}
	if (balance)
		g_core->quote = 1;
	else
		g_core->quote = 0;
	return (balance);
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
