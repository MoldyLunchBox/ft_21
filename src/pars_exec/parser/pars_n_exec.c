/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_n_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:10:35 by amya              #+#    #+#             */
/*   Updated: 2021/05/08 16:29:34 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	display_list2(t_red *list)
{
	t_red	*head;
	head = list;
	while(head)
	{
		ft_putstr("  ");
		ft_putendl(head->str);
		ft_putstr("         ");
		ft_putendl(head->red);
		head = head->next;
	}
}

void	display_list(t_cmd *list)
{
	t_cmd	*head;
	head = list;
	while(head)
	{
		ft_putendl(head->str);
		if (head->red)
			display_list2(head->red);
		head = head->next;
	}
}

int	execution(char *str)
{
	t_cmd	*list;

	list = command_parser(str, list);
	display_list(list);
	if (!main_list_loop(list))
	{
		ft_putstr("parss error");
		exit(0);
	}
	return 1;
}