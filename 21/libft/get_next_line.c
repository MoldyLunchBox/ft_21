/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:14:34 by amya              #+#    #+#             */
/*   Updated: 2019/04/24 06:27:28 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	constructor(char **s, char **line, int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[fd][i] != '\n' && s[fd][i] != '\0')
		i++;
	if (s[fd][i] == '\n')
	{
		*line = ft_strsub(s[fd], 0, i);
		tmp = ft_strdup(s[fd] + i + 1);
		free(s[fd]);
		s[fd] = tmp;
	}
	else if (s[fd][i] == '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*hold[4864];
	int			i;
	char		*tmp;

	if (fd < 0 || !line || fd > 4863)
		return (-1);
	i = 1;
	if (hold[fd] == NULL || ft_strchr(hold[fd], '\n') == NULL)
		while ((i = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[i] = '\0';
			if (!hold[fd])
				hold[fd] = ft_strnew(0);
			tmp = ft_strjoin(hold[fd], buff);
			free(hold[fd]);
			hold[fd] = tmp;
			if (ft_strchr(buff, '\n'))
				break ;
		}
	if (i < 0)
		return (-1);
	else if (i == 0 && (!hold[fd] || hold[fd][0] == '\0'))
		return (0);
	return (constructor(hold, line, fd));
}
