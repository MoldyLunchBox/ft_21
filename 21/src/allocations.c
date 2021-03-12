/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:06:56 by amya              #+#    #+#             */
/*   Updated: 2021/02/28 18:30:20 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

t_history	*create_node(void)
{
	t_history *temp;

	temp = ft_memalloc(sizeof(t_history));
	return (temp);
}

t_history	*modify_last_node(t_history *head, char *line)
{
	t_history	*temp;
	t_history	*p;
	char		*tmp;

	temp = ft_memalloc(sizeof(t_history));
	temp->line = ft_strdup(line);
	p = head;
	while (p->next != NULL)
		p = p->next;
	tmp = p->line;
	p->line = ft_strjoin(p->line, "\n");
	free(tmp);
	tmp = p->line;
	p->line = ft_strjoin(p->line, line + ft_strlen(DQUOTE_CMD));
	free(tmp);
	return (head);
}

t_history	*add_node(t_history *head, char *line)
{
	t_history *temp;
	t_history *p;

	temp = ft_memalloc(sizeof(t_history));
	temp->line = ft_strdup(line);
	if (head == NULL)
		head = temp;
	else
	{
		p = head;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
	}
	return (head);
}

void	select_line(t_history *head, int index)
{
	t_history *history;

	history = head;
	while (index)
	{
		history = history->next;
		index--;
	}
}
