/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:34:53 by amya              #+#    #+#             */
/*   Updated: 2021/03/22 17:46:29 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monkey_head.h"

int		is_printable(char *fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		if (((int)fd[i] >= 32 && (int)fd[i] < 127)
				|| (int)fd[i] == 9 || (int)fd[i] == 10)
			i++;
		else
			return (0);
	}
	return (1);
}

int		ft_iswhitespace(int c, int include_space)
{
	if (include_space)
		return (c == 127 || c == ' ' || c == '\t' ||
				c == '\n' || c == '\v' || c == '\f' || c == '\r');
	else
		return (c == 127 || c == '\t' || c == '\n' ||
				c == '\v' || c == '\f' || c == '\r');
}

int		str_is_whitespace(char *str, int include_space)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i], include_space))
			return (0);
		i++;
	}
	return (1);
}

int		is_not_button(char *fd)
{
	if (*((int *)fd) == COPY || *((int *)fd) == ALT_UP ||
			*((int *)fd) == ALT_DOWN || *((int *)fd) == CUT ||
			*((int *)fd) == PASTE || *((int *)fd) == ESC ||
			*((int *)fd) == KEY_UP
			|| *((int *)fd) == KEY_DOWN || *((int *)fd) == W_LEFT
			|| *((int *)fd) == W_RIGHT ||
			*((int *)fd) == KEY_LEFT || *((int *)fd) == KEY_RIGHT ||
			*((int *)fd) == KEY_DEL || *((int *)fd) == KEY_ENTER)
		return (0);
	else if (!is_printable(fd))
		return (0);
	return (1);
}

void	editing_keys(t_core *core, char *fd)
{
	if (*((int *)fd) == COPY)
		copy_paste(core, 1);
	else if (*((int *)fd) == PASTE)
		copy_paste(core, 2);
	else if (*((int *)fd) == CUT)
		cut(core);
	else if (*((int *)fd) == CTRL_D)
		ctrl_d2(core);
	else if (*((int *)fd) == KEY_DEL)
		del_letter(core);
}
