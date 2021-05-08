/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:09:50 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/22 15:47:18 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

int		get_left_fd(char *cmd, int i)
{
	int	ret;

	if (ft_isdigit(cmd[i - 1]) && (i - 2 < 0 || !cmd[i - 2]))
	{
		ret = ft_atoi(&cmd[i - 1]);
		return (ret);
	}
	return (-1);
}

char	*ft_herdoc(t_red *red)
{
	char	*her;
	char	*tmp;
	int		f_time;

	her = NULL;
	tmp = NULL;
	f_time = 0;
	while (red)
	{
		if (red->type & HERD)
		{
			if (f_time == 0)
				her = ft_strdup("");
			if (f_time == 0)
				f_time = 1;
			tmp = ft_strjoin(her, red->word);
			ft_strdel(&red->word);
			ft_strdel(&her);
			her = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		red = red->next;
	}
	return (her);
}

int		do_redirections_part_two(t_red *red)
{
	int fd;

	fd = -1;
	if (red->type & WRIT)
		fd = open(red->word, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (red->type & APPE)
		fd = open(red->word, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (red->type & READ)
		if ((fd = open(red->word, O_RDWR)) == -1)
		{
			mini_printf("can't open %s.\n", red->word);
			return (-1);
		}
	if (red->rfd == -2 && red->lfd == -1)
		dup2(fd, 2);
	if (red->type & READ)
		dup2(fd, 0);
	else if (red->lfd != -1)
		dup2(fd, red->lfd);
	else if (!(red->type & HERD))
		dup2(fd, 1);
	if (fd != -1)
		close(fd);
	return (0);
}

int		do_redirections(t_red *red)
{
	int fd;

	fd = -1;
	while (red)
	{
		if (!red->word)
		{
			if (red->lfd != -1)
				fd = red->lfd;
			else
				fd = 1;
			if (red->rfd < 0)
				close(red->lfd);
			else if (dup2(red->rfd, fd) == -1)
				return (-1);
		}
		else
		{
			if (do_redirections_part_two(red) == -1)
				return (-1);
		}
		red = red->next;
	}
	return (1);
}
