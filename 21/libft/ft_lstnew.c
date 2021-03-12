/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:25:14 by amya              #+#    #+#             */
/*   Updated: 2019/04/08 10:24:08 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*cont;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		cont = NULL;
		new->content_size = 0;
		new->content = (void *)cont;
		new->next = NULL;
		return (new);
	}
	if (!(cont = malloc(content_size)))
		return (NULL);
	new->content_size = content_size;
	ft_memcpy(cont, content, content_size);
	new->next = NULL;
	new->content = cont;
	return (new);
}
