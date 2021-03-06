/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:44:36 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 15:53:41 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	ft_echo(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		mini_printf("%s", str[i]);
		if (str[i + 1] != NULL)
			mini_printf(" ");
		i++;
	}
	mini_printf("\n");
}
