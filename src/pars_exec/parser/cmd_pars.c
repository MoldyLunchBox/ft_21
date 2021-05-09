/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 12:35:19 by amya              #+#    #+#             */
/*   Updated: 2021/05/09 11:53:13 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "monkey_head.h"

int	is_red(char c)
{
	if (c == '>' || c == '<' || ft_isdigit(c) || c == '&' || c == '-')
		return (1);
	return (0);
}
t_cmd	*add_pipe_col_node(t_cmd *head, char *line, int pipe_col)
{
	t_cmd *temp;
	t_cmd *p;

	temp = ft_memalloc(sizeof(t_cmd));
	temp->c = pipe_col;
	temp->str = ft_strdup(line);
	if (head == NULL)
		head = temp;
	else
	{
		p = head;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
	}
	return (head);
}

char	*pars_operators(char *str, int i)
{
	int		j;
	int		k;
	char	*ret;

	j = i;
	while ((str[i] && is_red(str[i])) | (str[i] && str[i] == ' '))
		i++;
	ret = ft_strsub(str, j, i - j);
	k = 0;
	j = 0;
	while(ret[j])
	{
		if (ret[j] != ' ')
		{
			ret[k] = ret[j];
			k++;
		}	
		j++;
	}
	ret[k] = '\0';
	return (ret);
}

t_red	*add_red_node(t_create_node_red *var, char *line, int pipe_col, int i)
{
	t_red *temp;
	t_red *p;

	temp = ft_memalloc(sizeof(t_red));
	temp->str = ft_strdup(line);
	temp->red = NULL;
	if (var->head->str[var->i])
		temp->red = pars_operators(var->head->str, i);
	else
		var->i--;
	if (var->head->red == NULL)
		var->head->red = temp;
	else
	{
		p = var->head->red;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
	}
	return (var->head->red);
}

t_cmd	*create_node_pipe_col(int *start, int end, char *str, t_cmd *list)
{
	char	*tmp;
	char	*del;
	int		pipe_col;

	if (str[end] == '|')
		pipe_col = 1;
	if (str[end] == ':')
		pipe_col = 2;
	else
		pipe_col = 0;
	tmp = NULL;
	if (str[end + 1] == '\0')
		end++;
	tmp = ft_strsub(str, *start, end - *start);
	if (tmp)
	{
		del = tmp;
		tmp = ft_strtrim(tmp);
		free(del);
		list = add_pipe_col_node(list, tmp, pipe_col);
	}
	free(tmp);
	*start = end + 1;
	return list;
}




t_red	*create_red_node(t_create_node_red *var)
{
	char	*tmp;
	int		pipe_col;
	int		i;

	i = var->i;
	if (var->head->str[var->i + 1])
		while (i > 0 && is_red(var->head->str[i]))
			i--;
	if (i < 0 || var->head->str[i] != ' ')
		i = var->i;
	var->r = 1;
	tmp = NULL;
	if (var->head->str[var->i + 1] == '\0')
		{var->i++;
		i++;}
	tmp = ft_strsub(var->head->str, var->start, i - var->start);
	if (tmp)
		var->head->red = add_red_node(var, tmp, pipe_col, i);
	free(tmp);
	var->start = var->i + 1;
	return var->head->red;
}

int	in_quote(char *str, int end)
{
	int	i;
	int	q;
	char	c;

	i = 0;
	c = '\0';
	q = -1;
	while(str[i] && i <= end)
	{
		if (str[i] == c && q == 1)
		{
			q *= -1;
			c = '\0';
			i++;
		}
		if (str[i] == '"' && q == -1 && c == '\0')
		{
			q *= -1;
			c = '"';
		}
		if (str[i] == '\'' && q == -1  && c == '\0')
		{
			q *= -1;
			c = '\'';
		}
		i++;
	}
	return q;
}
void	init_node_red(t_create_node_red *var, t_cmd	*list)
{
	var->i = 0;
	var->start = 0;
	var->head = list;
	var->r = 0;
}
t_cmd	*create_node_red(t_cmd **list, int node)
{
	t_create_node_red	var;

	init_node_red(&var, *list);
	while (var.head)
	{
		if(var.i == node)
		{
			var.i = 0;
			while (var.head->str[var.i])
			{
				if ((var.head->str[var.i] == '<' || var.head->str[var.i] == '>'
				|| (var.head->str[var.i+1] == '\0' && var.r)) && in_quote(var.head->str, var.i) == -1)
					var.head->red = create_red_node(&var);
				var.i++;
			}
			break ;
		}
		var.i++;
		var.head = var.head->next;
	}
	return (*list);
}

t_cmd *	command_parser(char *str, t_cmd *list)
{
	int		end;
	int		start;
	int		node;

	end = 0;
	start = 0;
	list = NULL;
	node = 0;
	while (str[end])
	{
		if ((str[end] == '|' || str[end] == ':' || str[end + 1] == '\0') && in_quote(str, end) == -1)
		{
			list = create_node_pipe_col(&start, end, str, list);
			list = create_node_red(&list, node);
			node++;
		}
		end++;
	}
	return list;
}