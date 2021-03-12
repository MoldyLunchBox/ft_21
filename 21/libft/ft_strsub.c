/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:01:12 by homadani          #+#    #+#             */
/*   Updated: 2019/04/22 17:39:33 by homadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*out;

	i = 0;
	if (!s)
		return (NULL);
	if (!(out = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		out[i] = s[start];
		i++;
		start++;
	}
	out[i] = '\0';
	return (out);
}
