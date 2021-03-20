/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:47:35 by amya              #+#    #+#             */
/*   Updated: 2021/03/20 14:54:19 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/monkey_head.h"

void	handle_quotes(char c, int *balance)
{
	if (c == '\"' && *balance == 0)
		*balance = 2;
	else if (c == '\'' && *balance == 0)
		*balance = 1;
	else if (c == '\"' && *balance == 2)
		*balance = 0;
	else if (c == '\'' && *balance == 1)
		*balance = 0;
}

int		check_quotes(char *str)
{
	int	i;
	int	balance;

	i = 0;
	balance = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quotes(str[i], &balance);
		i++;
	}
	if (balance)
		g_core->quote = 1;
	else
		g_core->quote = 0;
	return (balance);
}
