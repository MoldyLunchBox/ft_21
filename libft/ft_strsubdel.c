/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:02:07 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/18 17:02:01 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubdel(char **str, int start, int finish)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((ft_strlen(*str) - (finish - start)) == 0)
	{
		ft_strdel(str);
		res = ft_strdup((char[]){1, 0});
		return (res);
	}
	if (!(res = (char *)ft_memalloc(sizeof(char) *
					ft_strlen(*str) - (finish - start) + 1)))
		return (NULL);
	while ((*str)[i])
	{
		i = (i == start) ? finish : i;
		if ((*str)[i] == '\0')
			break ;
		res[j++] = (*str)[i++];
	}
	res[j] = '\0';
	ft_strdel(str);
	return (res);
}
