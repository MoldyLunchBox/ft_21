/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tosh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:49:03 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/22 15:01:55 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	split_them(t_t **tail, char **env, int index)
{
	char	**temp_var;

	temp_var = ft_strsplit(env[index], '=');
	(*tail)->key = NULL;
	(*tail)->value = NULL;
	if (temp_var[0])
		(*tail)->key = ft_strdup(temp_var[0]);
	else
		(*tail)->key = ft_strdup("");
	if (temp_var[1])
		(*tail)->value = ft_strdup(temp_var[1]);
	else
		(*tail)->value = ft_strdup("");
	free_2d(&temp_var);
}

t_t		*init_env(char **env)
{
	t_t	*actual_env;
	t_t	*tail;
	int	i;

	tail = NULL;
	actual_env = NULL;
	i = -1;
	if (!(actual_env = (t_t *)ft_memalloc(sizeof(t_t))) || env[0] == NULL)
		return (NULL);
	actual_env->next = NULL;
	tail = actual_env;
	while (env[++i])
	{
		split_them(&tail, env, i);
		if (!env[i + 1])
			break ;
		if (!(tail->next = (t_t *)ft_memalloc(sizeof(t_t))))
			return (NULL);
		tail = tail->next;
	}
	tail->next = NULL;
	return (actual_env);
}

int		skip_chars(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

int		tosh(char **input, t_t **env, int *ac, char ***av)
{
	(void)*ac;
	(void)*av;
	g_checker = 1;
	if (!(*input) || skip_chars(*input))
	{
		ft_strdel(input);
		return (-1);
	}
	if (!ft_strncmp(*input, "exit", ft_strlen("exit")))
	{
		ft_strdel(input);
		unconfigure_term();
		if (g_core->line)
			free(g_core->line);
		if (g_core->copy)
			free(g_core->copy);
		if (g_core->history)
			free_struct(g_core->history);
		return (0);
	}
	*env = do_everything(*input, *env);
	ft_strdel(input);
	return (1);
}
