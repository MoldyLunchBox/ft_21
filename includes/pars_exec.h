/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 12:37:59 by amya              #+#    #+#             */
/*   Updated: 2021/05/08 12:24:00 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_EXEC_H
# define PARS_EXEC_H

# include "../libft/libft.h"
# include "monkey_head.h"
# include <sys/wait.h>
# include <dirent.h>



enum 
{
	// IO_NUMBER = "IO_NUMBER",
	SUP,//  ">",
	ANDSUP,//  "&>",
	DSUP,// >",
	ANDDSUP,//  "&>>",
	INF,//  "<",
	DINF,//  "<<",
	SUPAND,//  ">&",
	INFAND,//  "<&",
	SUPANDDASH,//  ">&-",
	INFANDDASH,//  "<&-",
}	t_enum;
typedef struct	s_red
{
	char	*str;
	char	*red;
	struct s_red *next;
}				t_red;

typedef struct	s_cmd
{
	char	*str;
	int		c;
	t_red	*red;
	struct s_cmd *next;
}				t_cmd;

typedef struct	s_create_node_red
{
	t_cmd	*head;
	int		i;
	int		start;
	int		r;
}				t_create_node_red;

t_cmd *	command_parser(char *str, t_cmd *list);
t_cmd*	create_node(int *start, int end, char *str, t_cmd *list);
t_cmd	*add_node2(t_cmd *head, char *line, int pipe_red);
int		execution(char *str);
#endif