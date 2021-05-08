/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:47:44 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/22 17:55:42 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

void	go_to_w_left(t_core *core)
{
	int i;

	i = core->real_pos;
	if (i > core->pre_cmd)
	{
		if (ft_isalnum(core->line[i]))
			while (i > core->pre_cmd && ft_isalnum(core->line[i]))
				i--;
		if (!ft_isalnum(core->line[i]))
			while (i > core->pre_cmd && !ft_isalnum(core->line[i]))
				i--;
		if (ft_isalnum(core->line[i]))
			while (i > core->pre_cmd && ft_isalnum(core->line[i]))
				i--;
	}
	if (i > core->pre_cmd)
		i++;
	core->real_pos = i;
	print_line(core, 1);
}

void	go_to_w_right(t_core *core)
{
	int i;
	int len;

	len = ft_strlen(core->line);
	i = core->real_pos;
	if (i < len)
	{
		if (ft_isalnum(core->line[i]))
			while (i < len && ft_isalnum(core->line[i]))
				i++;
		if (!ft_isalnum(core->line[i]))
			while (i < len && !ft_isalnum(core->line[i]))
				i++;
	}
	core->real_pos = i;
	print_line(core, 1);
}
