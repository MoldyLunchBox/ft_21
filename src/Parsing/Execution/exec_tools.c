/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:28:54 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 15:53:02 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	free_cmd_list(t_cmd **lst)
{
	t_cmd	*tail;

	while (*lst)
	{
		tail = *lst;
		(*lst) = (*lst)->next;
		free_2d(&(tail->cmd));
		free(tail);
	}
}

void	check_perm(char *path)
{
	if (access(path, F_OK) == 0)
		mini_printf("%s: Permission Denied.\n", path);
	else
		mini_printf("%s: Command not found.\n", path);
}

int		check_file(char *path)
{
	if (access(path, F_OK) != -1)
		return (1);
	return (0);
}

char	*brute_force(char *cmd, char *path_env)
{
	char	**tab;
	char	*tmp;
	char	*tmp2;
	int		i;

	if (!path_env || !(tab = ft_strsplit(path_env, ':')))
		return (ft_strdup(cmd));
	i = -1;
	tmp = NULL;
	tmp2 = NULL;
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (check_file(tmp2))
		{
			free_2d(&tab);
			return (tmp2);
		}
		free(tmp2);
	}
	free_2d(&tab);
	return (ft_strdup(cmd));
}

char	*get_full_path(char *cmd, t_t *env)
{
	char	*full_path;

	if (!(check_file(cmd) && cmd[0] != '.' &&
		cmd[0] != '/') &&
		!check_builtins(cmd))
		full_path = brute_force(cmd, ft_lstsearch(env, "PATH"));
	else
		full_path = ft_strdup(cmd);
	return (full_path);
}
