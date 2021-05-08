/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_about_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:18:21 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 15:53:02 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	manage_fds(int flag)
{
	static int	stdin;
	static int	stdout;
	static int	stderr;

	if (flag == 1)
	{
		stdin = dup2(0, 167);
		stdout = dup2(1, 168);
		stderr = dup2(2, 169);
	}
	else if (flag == 2)
		dup2(stdout, 1);
	else
	{
		dup2(stdin, 0);
		dup2(stdout, 1);
		dup2(stderr, 2);
		if (flag == 3)
		{
			close(stdin);
			close(stdout);
			close(stderr);
		}
	}
}

int		manage_pipes2(int flag)
{
	static int	fd[2];

	if (flag == -1)
	{
		if (pipe(fd) == -1)
			exit(1);
		dup2(fd[1], 1);
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		return (-1);
	}
}

int		manage_pipes(t_cmd *lst)
{
	static int	p0 = -1;
	static char	*heredoc = NULL;

	if (p0 == -1)
		heredoc = ft_herdoc(lst->red);
	if (p0 != -1)
		p0 = manage_pipes2(p0);
	if (lst->next || heredoc)
		p0 = manage_pipes2(-1);
	if (heredoc != NULL)
	{
		ft_putstr(heredoc);
		ft_strdel(&heredoc);
		manage_fds(2);
		return (-2);
	}
	if (lst->red != NULL)
		if (do_redirections(lst->red) == -1)
			return (-3);
	return (p0);
}
