/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:53:37 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/22 15:47:22 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

int		find_red_index(char *str, int i)
{
	int	balance;

	balance = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quotes(str[i], &balance);
		if ((str[i] == '<' || str[i] == '>') && balance == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		get_red_type(char *cmd, int *i)
{
	if (!ft_strncmp(&cmd[*i], "<<", 2))
	{
		(*i) += 2;
		if (cmd[*i] == '&')
			return (-1);
		return (HERD);
	}
	else if (!ft_strncmp(&cmd[*i], "<", 1))
	{
		(*i)++;
		return (READ);
	}
	else if (!ft_strncmp(&cmd[*i], ">>", 2))
	{
		(*i) += 2;
		if (cmd[*i] == '&')
			(*i)++;
		return (APPE);
	}
	else
	{
		(*i)++;
		return (WRIT);
	}
	return (-1);
}

int		real_parse_red(char **cmd, int i, t_red **red, char **cmd2)
{
	int	start;
	int	checker;

	start = i;
	checker = 0;
	(*red)->lfd = get_left_fd(*cmd, i);
	if (((*red)->type = get_red_type(*cmd, &i)) < 0)
		return (-1);
	(*red)->rfd = get_right_fd(*cmd, &i);
	if ((*red)->rfd == -1 || (*red)->rfd == -2)
	{
		if (!((*red)->word = get_word(*cmd, &i, *cmd2, &checker)))
			return (-1);
	}
	else
		(*red)->word = NULL;
	if ((*red)->type & HERD)
		do_herdoc(&(*red)->word);
	if ((*red)->lfd != -1)
		start = start - 1;
	*cmd = ft_strsubdel(cmd, start, i);
	if (checker)
		*cmd2 = ft_strsubdel(cmd2, 0, checker);
	return (1);
}

int		p_two(char **cmd, t_red **red, char **cmd2)
{
	int		i;
	t_red	*tail;
	t_red	*head;

	i = 0;
	tail = *red;
	while ((*cmd)[i])
	{
		if ((i = find_red_index(*cmd, i)) < 0)
			return (0);
		tail = (t_red *)ft_memalloc(sizeof(t_red));
		head = (!*red) ? tail : *red;
		if (*red)
			while (head->next)
				head = head->next;
		if ((i = real_parse_red(cmd, i, &tail, cmd2)) < 0)
			return (e2(red, &tail));
		if (!*red)
			*red = head;
		else
			head->next = tail;
	}
	return (1);
}

int		parse_redirections(t_ast **tail)
{
	t_ast	*fir_tail;
	t_list	*sec_tail;
	char	*temp;

	temp = NULL;
	fir_tail = *tail;
	while (fir_tail)
	{
		sec_tail = fir_tail->cmd;
		while (sec_tail)
		{
			temp = (!sec_tail->next) ? NULL :
				ft_strdup((char *)sec_tail->next->content);
			if (p_two((char **)&sec_tail->content, &fir_tail->red, &temp) < 0)
				return (e((char **)&sec_tail->next->content, &temp, 1));
			if (temp)
				e((char **)&sec_tail->next->content, &temp, 2);
			sec_tail = sec_tail->next;
		}
		if (!fir_tail->pip && !fir_tail->sep)
			break ;
		fir_tail = (fir_tail->pip) ? fir_tail->pip : fir_tail->sep;
	}
	clean_ast(tail);
	return (1);
}
