/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_everything.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:50:11 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 15:36:50 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	remove_quotes_pt2(char **str)
{
	int		i;
	int		len;
	int		b;
	int		j;

	i = 0;
	len = ft_strlen(*str);
	b = 0;
	while (i < len)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			handle_quotes((*str)[i], &b);
		if (((*str)[i] == '"' && (b == 0 || b == 2)) ||
			((*str)[i] == '\'' && (b == 0 || b == 1)))
		{
			j = i - 1;
			while (++j < len)
				(*str)[j] = (*str)[1 + j];
			len--;
			i--;
		}
		i++;
	}
}

void	remove_quotes(t_ast **ast)
{
	t_ast	*tail;
	t_list	*lst;
	char	*tmp;

	tail = *ast;
	while (tail)
	{
		lst = tail->cmd;
		while (lst)
		{
			tmp = (char *)lst->content;
			remove_quotes_pt2(&tmp);
			lst = lst->next;
		}
		if (tail->sep)
			tail = tail->sep;
		else if (tail->pip)
			tail = tail->pip;
		else
			break ;
	}
}

void	do_expansions(t_ast *ast, t_t *env)
{
	t_ast	*tail;
	t_list	*lst;
	char	**cmd;

	tail = ast;
	while (tail)
	{
		lst = tail->cmd;
		while (lst)
		{
			cmd = (char **)ft_memalloc(sizeof(char *) * 2);
			cmd[0] = ft_strdup((char *)lst->content);
			cmd[1] = NULL;
			free(lst->content);
			expansions(&cmd, env);
			lst->content = ft_strdup(cmd[0]);
			free_2d(&cmd);
			lst = lst->next;
		}
		if (!tail->pip && !tail->sep)
			break ;
		tail = (tail->pip) ? tail->pip : tail->sep;
	}
}

t_t		*parser_err_managing(t_ast **ast, char c, t_t *env)
{
	if (!c)
		mini_printf("21sh: Parsing error.\n");
	else
	{
		mini_printf("21sh: Parsing error near '");
		ft_putchar(c);
		mini_printf("'\n");
	}
	free_ast(ast);
	return (env);
}

t_t		*do_everything(char *input, t_t *env)
{
	t_ast	*ast;
	t_ast	*tail;
	t_d		do_e;

	ast = NULL;
	ast = (t_ast *)ft_memalloc(sizeof(t_ast));
	tail = ast;
	do_e.i = 0;
	do_e.old_i = 0;
	do_e.balance = 0;
	do_e.n_str = NULL;
	if ((do_e.err_char = parser(input, &tail, do_e)) != 's')
		return (parser_err_managing(&ast, do_e.err_char, env));
	tail = ast;
	do_expansions(tail, env);
	tail = ast;
	if (parse_redirections(&tail) < 0)
		return (parser_err_managing(&ast, 0, env));
	tail = ast;
	remove_quotes(&tail);
	env = execute_ast(ast, env);
	free_ast(&ast);
	return (env);
}
