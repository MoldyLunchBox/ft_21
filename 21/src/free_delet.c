/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_delet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:08:25 by amya              #+#    #+#             */
/*   Updated: 2020/03/10 13:08:27 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

// void		free_struct(t_core *core)
// {
// 	t_names *tmp;

// 	while (core->names)
// 	{
// 		tmp = core->names;
// 		if (core->names->select)
// 			free(core->names->select);
// 		free(core->names->name);
// 		core->names = core->names->next;
// 		free(tmp);
// 	}
// }

// void		free_to_leave(t_core *core, int show)
// {
// 	unconfigure_term();
// 	if (show)
// 		show_selected(core);
// 	free_struct(core);
// 	exit(0);
// }

// void		free_runner(t_names *runner)
// {
// 	if (runner->select)
// 		free(runner->select);
// 	free(runner->name);
// 	free(runner);
// }

// void		delet_item(t_core *core)
// {
// 	t_names	*runner;
// 	t_names	*previous;
// 	int		i;

// 	i = 0;
// 	previous = NULL;
// 	runner = core->names;
// 	ft_putstr_fd(tgetstr("cl", NULL), 2);
// 	while (runner)
// 	{
// 		if (core->index == i++)
// 		{
// 			if (previous)
// 				previous->next = runner->next;
// 			if (!previous)
// 				core->names = runner->next;
// 			free_runner(runner);
// 			core->argc--;
// 			if (core->index > core->argc - 1)
// 				core->index--;
// 			break ;
// 		}
// 		previous = runner;
// 		runner = runner->next;
// 	}
// }
