/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:05:18 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 16:42:28 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	fill_executing(t_cmd **lst, t_cmd **pss, t_ast **tail, int flag)
{
	if (flag == 1 || flag == 0)
	{
		(*lst) = (t_cmd *)ft_memalloc(sizeof(t_cmd));
		(*lst)->cmd = list_to_array((*tail)->cmd);
		(*lst)->red = (*tail)->red;
		(*lst)->next = NULL;
		if (flag == 0)
		{
			(*pss) = (*lst);
			(*tail) = (*tail)->pip;
		}
	}
	else if (flag == 2 || flag == 3)
	{
		(*pss)->next = (t_cmd *)ft_memalloc(sizeof(t_cmd));
		(*pss) = (*pss)->next;
		(*pss)->cmd = list_to_array((*tail)->cmd);
		(*pss)->red = (*tail)->red;
		(*pss)->next = NULL;
		if (flag == 2)
			(*tail) = (*tail)->pip;
	}
}

void	init_vars_and_free(t_ex *ex, t_ast *ast, t_cmd **lst, int f)
{
	if (f == 1)
		manage_fds(1);
	if (ast)
	{
		ex->tail = ast;
		ex->lst = NULL;
		ex->pss = NULL;
	}
	else
	{
		free_cmd_list(lst);
		ex->tail = ex->tail->sep;
	}
}

void	ft_execve(t_cmd *lst, char **a_env, int i, t_t *env)
{
	char	*full_path;

	if (!fork())
	{
		if (i != -1)
			close(i);
		full_path = get_full_path(lst->cmd[0], env);
		if (execve(full_path, lst->cmd, a_env))
		{
			check_perm(full_path);
			exit(1);
		}
	}
	else
	{
		manage_fds(0);
		if (!lst->next)
		{
			while (wait(0) > 0)
				;
		}
	}
}

t_t		*execute_ast_pt2(t_cmd *lst, t_t *env)
{
	char	**a_env;
	int		i;

	while (lst)
	{
		a_env = env_to_array(env);
		if ((i = manage_pipes(lst)) <= -2)
		{
			free_2d(&a_env);
			if (i == -3)
				while (lst)
					lst = lst->next;
			continue ;
		}
		if (!check_builtins(lst->cmd[0]))
			ft_execve(lst, a_env, i, env);
		else
		{
			do_builtins(&lst->cmd, &env, NULL);
			manage_fds(0);
		}
		free_2d(&a_env);
		lst = lst->next;
	}
	return (env);
}

t_t		*execute_ast(t_ast *ast, t_t *env)
{
	t_ex	ex;

	init_vars_and_free(&ex, ast, NULL, 1);
	while (ex.tail)
	{
		if (ex.tail->pip)
		{
			while (ex.tail->pip)
				(!ex.lst) ? fill_executing(&ex.lst, &ex.pss, &ex.tail, 0) :
					fill_executing(&ex.lst, &ex.pss, &ex.tail, 2);
			fill_executing(&ex.lst, &ex.pss, &ex.tail, 3);
		}
		else
		{
			if (!ex.lst)
				fill_executing(&ex.lst, &ex.pss, &ex.tail, 1);
			if (ex.lst->cmd && ex.lst->cmd[0])
				env = execute_ast_pt2(ex.lst, env);
			init_vars_and_free(&ex, NULL, &ex.lst, 0);
			if (ex.tail && !ex.tail->cmd)
				break ;
		}
	}
	manage_fds(3);
	return (env);
}
