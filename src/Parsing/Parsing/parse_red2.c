/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:59:54 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/24 14:39:28 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	do_herdoc(char **word)
{
	char	*ret;
	char	*input;
	int		i;

	g_core->heredoc = 1;
	g_checker = 0;
	ret = ft_strdup("");
	i = 0;
	while (1)
	{
		init_term2(g_core);
		input = readline(g_core);
		unconfigure_term();
		ft_putendl("");
		if (g_core->heredoc)
		{

		input = (!input) ? ft_strdup("") : input;
		if (!ft_strcmp(input, *word))
		{
			i = 2;
			ft_strdel(word);
			*word = ft_strdup(ret);
			its_just_me(&ret, &input, &i, NULL);
			break ;
		}
		its_just_me(&input, &ret, &i, NULL);
		}
		else 
			break;
	}
}

void	delete_key(t_list **head, char *key)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *head;
	while (tmp != NULL && !ft_strcmp(tmp->content, key))
	{
		*head = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = *head;
	}
	while (tmp != NULL)
	{
		while (tmp != NULL && ft_strcmp(tmp->content, key))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			break ;
		prev->next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = prev->next;
	}
}

void	clean_ast(t_ast **ast)
{
	char	*key;

	key = ft_strdup((char[]){1, 0});
	while (*ast)
	{
		delete_key(&(*ast)->cmd, key);
		if ((*ast)->pip)
			(*ast) = (*ast)->pip;
		else if ((*ast)->sep)
			(*ast) = (*ast)->sep;
		else
			break ;
	}
	ft_strdel(&key);
}

int		get_right_fd(char *cmd, int *i)
{
	int		j;
	char	*fd;
	int		t_fd;

	if (cmd[*i] != '&')
		return (-1);
	(*i)++;
	if (!cmd[*i])
		return (-2);
	j = (*i);
	if (cmd[j] == '-')
		j++;
	while (cmd[j])
	{
		if (!ft_isdigit(cmd[j]))
			return (-1);
		j++;
	}
	fd = ft_strsub(cmd, *i, j);
	t_fd = (fd[0] == '-') ? -5 : ft_atoi(fd);
	*i = j;
	ft_strdel(&fd);
	return (t_fd);
}

char	*get_word(char *cmd, int *i, char *cmd2, int *checker)
{
	int		start;
	int		len;
	char	*temp;
	int		balance;

	temp = (cmd[*i]) ? cmd : cmd2;
	start = (cmd[*i]) ? *i : 0;
	*checker = (cmd[*i] == '\0') ? 1 : *checker;
	len = start - 1;
	balance = 0;
	if (!temp)
		return (NULL);
	while (temp[++len] && temp[len] != '>' && temp[len] != '<' && balance == 0)
	{
		if (temp[len] == '\'' || temp[len] == '"')
			handle_quotes(temp[len], &balance);
		(*checker) += (*checker) ? 1 : 0;
		if (!*checker)
			(*i)++;
	}
	(*checker) -= (*checker) ? 1 : 0;
	if (!temp || len - start <= 0)
		return (NULL);
	return (ft_strsub(temp, start, (len - start < 0) ? 0 : len - start));
}
