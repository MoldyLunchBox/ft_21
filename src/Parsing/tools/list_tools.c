/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:07:29 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/20 16:28:42 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

int			lst_size(t_t *env)
{
	int		i;
	t_t		*fresh;

	i = 0;
	fresh = env;
	while (fresh != NULL)
	{
		i++;
		fresh = fresh->next;
	}
	return (i);
}

char		**env_to_array(t_t *env)
{
	t_t		*tail;
	char	**a_env;
	int		i;
	char	*str_one;
	char	*str_two;

	a_env = (char **)ft_memalloc(sizeof(char *) * (lst_size(env) + 1));
	a_env[lst_size(env)] = NULL;
	tail = env;
	i = 0;
	while (tail)
	{
		str_one = ft_strjoin(tail->key, "=");
		str_two = ft_strjoin(str_one, tail->value);
		a_env[i++] = ft_strdup(str_two);
		ft_strdel(&str_one);
		ft_strdel(&str_two);
		tail = tail->next;
	}
	return (a_env);
}

char		**list_to_array(t_list *alst)
{
	t_list	*tail;
	int		i;
	char	**array;

	tail = alst;
	i = 0;
	while (tail)
	{
		i++;
		tail = tail->next;
	}
	array = (char **)ft_memalloc(sizeof(char *) * i + 1);
	tail = alst;
	i = 0;
	while (tail)
	{
		array[i] = ft_strdup(tail->content);
		i++;
		tail = tail->next;
	}
	array[i] = NULL;
	return (array);
}

void		free_env(t_t **env)
{
	t_t *fresh;

	while ((*env) != NULL)
	{
		fresh = *env;
		(*env) = (*env)->next;
		ft_strdel(&fresh->key);
		ft_strdel(&fresh->value);
		free(fresh);
	}
}

char		*ft_lstsearch(t_t *env, char *to_search)
{
	t_t		*fresh;

	fresh = env;
	while (fresh != NULL)
	{
		if (!(ft_strcmp(fresh->key, to_search)))
			return (fresh->value);
		fresh = fresh->next;
	}
	return (NULL);
}
