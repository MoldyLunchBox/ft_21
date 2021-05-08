/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:51:54 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 15:53:02 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

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

void	fill_infos_two(t_p *vars, char *str, int balance)
{
	if (ft_isspace(str[vars->i]) && balance == 0)
	{
		if (vars->buff != NULL)
			ft_lstadd_back(&vars->lst, ft_lstnew(vars->buff,
				ft_strlen(vars->buff) + 1));
		ft_strdel(&(vars->buff));
	}
	else if (!ft_isspace(str[vars->i]) || balance != 0)
	{
		if (vars->buff == NULL)
			vars->buff = ft_strjoin("", (char[]){str[vars->i], 0});
		else
		{
			vars->temp = ft_strdup(vars->buff);
			ft_strdel(&(vars->buff));
			vars->buff = ft_strjoin(vars->temp, (char[]){str[vars->i], 0});
			ft_strdel(&(vars->temp));
		}
	}
}

t_list	*parser_two(char *str)
{
	t_p vars;

	vars.i = 0;
	vars.lst = NULL;
	vars.balance = 0;
	vars.buff = NULL;
	vars.temp = NULL;
	while (str[vars.i])
	{
		if (str[vars.i] == '\'' || str[vars.i] == '\"')
			handle_quotes(str[vars.i], &vars.balance);
		fill_infos_two(&vars, str, vars.balance);
		vars.i++;
	}
	if (vars.buff != NULL)
		ft_lstadd_back(&vars.lst, ft_lstnew(vars.buff,
					ft_strlen(vars.buff) + 1));
	ft_strdel(&vars.buff);
	return (vars.lst);
}

int		fill_infos(t_d *do_e, char *input, t_ast **tail, int flag)
{
	do_e->n_str = ft_strsub(input, do_e->old_i, do_e->i - do_e->old_i);
	if (!ft_strcmp(do_e->n_str, "") || !do_e->n_str ||
		!((*tail)->cmd = parser_two(do_e->n_str)))
	{
		ft_strdel(&do_e->n_str);
		return (0);
	}
	ft_strdel(&do_e->n_str);
	if (flag == 1)
	{
		do_e->last_sign = input[do_e->i];
		if (input[do_e->i] == ';')
		{
			(*tail)->sep = (t_ast *)ft_memalloc(sizeof(t_ast));
			*tail = (*tail)->sep;
		}
		else
		{
			(*tail)->pip = (t_ast *)ft_memalloc(sizeof(t_ast));
			*tail = (*tail)->pip;
		}
	}
	return (1);
}

char	parser(char *input, t_ast **tail, t_d do_e)
{
	while (input[do_e.i])
	{
		if (input[do_e.i] == '\'' || input[do_e.i] == '\"')
			handle_quotes(input[do_e.i], &do_e.balance);
		if ((input[do_e.i] == ';' || input[do_e.i] == '|') && do_e.balance == 0)
		{
			if (!fill_infos(&do_e, input, tail, 1))
				return (input[do_e.i]);
			do_e.old_i = do_e.i + 1;
		}
		do_e.i++;
	}
	if (input[do_e.old_i])
	{
		if (!fill_infos(&do_e, input, tail, 0))
			return (0);
	}
	if (!(*tail)->cmd && do_e.last_sign != ';')
		return ('|');
	return ('s');
}
