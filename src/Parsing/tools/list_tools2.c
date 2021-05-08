/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:06:51 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 16:28:44 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	free_list(t_list **lst)
{
	t_list	*tail;

	while (*lst)
	{
		tail = *lst;
		*lst = (*lst)->next;
		ft_strdel((char **)&tail->content);
		free(tail);
		tail = NULL;
	}
}

void	free_red_list(t_red **red)
{
	t_red	*tail;

	while (*red)
	{
		tail = *red;
		*red = (*red)->next;
		ft_strdel(&tail->word);
		free(tail);
		tail = NULL;
	}
}

void	free_ast(t_ast **ast)
{
	t_ast	*tail;

	while (*ast)
	{
		tail = *ast;
		free_list(&tail->cmd);
		free_red_list(&tail->red);
		free(tail);
		tail = NULL;
		if ((*ast)->sep)
			*ast = (*ast)->sep;
		else if ((*ast)->pip)
			*ast = (*ast)->pip;
		else
			break ;
	}
}

int		e2(t_red **red, t_red **tail)
{
	free_red_list(red);
	free(*tail);
	return (-1);
}

int		e(char **str, char **temp, int f)
{
	if (f == 1)
	{
		ft_strdel(temp);
		return (-1);
	}
	else if (f == 2)
	{
		ft_strdel(str);
		*str = ft_strdup(*temp);
		ft_strdel(temp);
	}
	return (1);
}
