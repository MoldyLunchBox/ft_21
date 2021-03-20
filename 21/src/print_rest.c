/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:57:43 by amya              #+#    #+#             */
/*   Updated: 2021/03/20 14:43:41 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

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

int		fd_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int		ft_putchar_int(int c)
{
	ft_putchar((char)c);
	return (0);
}