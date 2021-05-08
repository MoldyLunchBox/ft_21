/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:02:56 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/22 15:22:21 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tosh.h"

void	tilda(char **tab, t_t *env)
{
	char	*home;
	char	*res;

	home = NULL;
	res = NULL;
	if (!(home = ft_lstsearch(env, "HOME")))
		return ;
	res = ft_strjoin(home, &(*tab)[1]);
	free(*tab);
	*tab = ft_strdup(res);
	free(res);
}

int		check_symb(char *str, int index)
{
	while (str[index] && ft_isalnum(str[index]))
		index++;
	return (index);
}

void	its_just_me(char **tmp, char **teemp, int *i, char *tab)
{
	char	*temp;
	char	*temp2;

	if (!tab)
	{
		if (*i == 2)
		{
			ft_strdel(tmp);
			ft_strdel(teemp);
			return ;
		}
		temp = ft_strjoin(*tmp, "\n");
		temp2 = ft_strjoin(*teemp, temp);
		ft_strdel(tmp);
		ft_strdel(teemp);
		*teemp = ft_strdup(temp2);
		ft_strdel(&temp);
		ft_strdel(&temp2);
	}
	else
	{
		ft_strdel(tmp);
		ft_strdel(teemp);
		*i = check_symb(tab, (*i) + 1);
	}
}

void	do_dollar(char *tab, t_t *env, char **new_str, int i)
{
	char	*tmp;
	char	*var;
	char	*teemp;
	int		b;

	i = 0;
	b = 0;
	while (tab[i])
	{
		if (tab[i] == '\'' || tab[i] == '"')
			handle_quotes(tab[i], &b);
		if (tab[i] == '$' && tab[i + 1] && (b == 0 || b == 2))
		{
			var = ft_strsub(tab, i, check_symb(tab, i + 1) - i);
			tmp = (!ft_lstsearch(env, ft_strchr(var, '$') + 1)) ? ft_strdup("")
				: ft_strdup(ft_lstsearch(env, ft_strchr(var, '$') + 1));
			ft_strdel(&var);
		}
		else
			tmp = ft_strsub(tab, i, check_symb(tab, i + 1) - i);
		teemp = ft_strdup(*new_str);
		ft_strdel(&(*new_str));
		(*new_str) = ft_strjoin(teemp, tmp);
		its_just_me(&tmp, &teemp, &i, tab);
	}
}

void	expansions(char ***tab, t_t *env)
{
	int		i;
	char	*new_str;
	int		balance;

	i = 0;
	balance = 0;
	while ((*tab)[i] != NULL)
	{
		if ((*tab)[i][0] == '~' && ((*tab)[i][1] == '/' || !(*tab)[i][1]))
			tilda(&(*tab)[i], env);
		else
		{
			new_str = ft_strdup("");
			do_dollar((*tab)[i], env, &new_str, 0);
			ft_strdel(&(*tab)[i]);
			(*tab)[i] = ft_strdup(new_str);
			ft_strdel(&new_str);
		}
		i++;
	}
}
