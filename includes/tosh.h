/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tosh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmzah <hmzah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:10:38 by hmzah             #+#    #+#             */
/*   Updated: 2021/03/22 14:52:30 by hmzah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H

# include "../libft/libft.h"
# include "monkey_head.h"
# include <sys/wait.h>
# include <dirent.h>

/*
**		Define.
*/

# define WRIT		1
# define APPE		2
# define READ		4
# define HERD		8
# define MAX_SIZE	1024

/*
**		Structures.
*/

typedef struct		s_red
{
	char			*word;
	int				type;
	int				lfd;
	int				rfd;
	struct s_red	*next;
}					t_red;

typedef struct		s_cmd
{
	char			**cmd;
	t_red			*red;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_t;

typedef struct		s_ast
{
	t_list			*cmd;
	t_red			*red;
	struct s_ast	*sep;
	struct s_ast	*pip;
}					t_ast;

/*
**		Structures used to replace variables in big functions.
**		Named after the function.
*/

typedef struct		s_ex_ast
{
	t_ast			*tail;
	t_cmd			*lst;
	t_cmd			*pss;
}					t_ex;

typedef struct		s_do_everything
{
	int				i;
	int				old_i;
	char			*n_str;
	int				balance;
	char			last_sign;
	char			err_char;
}					t_d;

typedef struct		s_parser_two
{
	t_list			*lst;
	int				i;
	int				balance;
	char			*buff;
	char			*temp;
	int				add;
}					t_p;

typedef struct		s_execute_ast
{
	char			**cmd;
	char			*full_path;
	int				is_pip;
	int				f_time;
	int				l_time;
}					t_e;

/*
**		Functions.
*/

/*
**		src/tosh.c
*/

t_t					*init_env(char **env);
int					tosh(char **input, t_t **env, int *ac, char ***av);

/*
**		src/do_everything.c
*/

t_t					*do_everything(char *input, t_t *env);

/*
**		src/parser.c
*/

void				handle_quotes(char c, int *balance);
char				parser(char *input, t_ast **tail, t_d do_e);

/*
**		src/parse_red.c
*/

int					parse_redirections(t_ast **tail);

/*
**		src/parse_red2.c
*/

void				do_herdoc(char **word);
void				clean_ast(t_ast **ast);
int					get_right_fd(char *cmd, int *i);
char				*get_word(char *cmd, int *i, char *cmd2, int *checker);

/*
**		src/fill_red.c
*/

int					fill_type(char *cmd, int index);
int					fill_rfd(char *cmd, int *index);

/*
**		src/executing.c
*/

t_t					*execute_ast(t_ast *ast, t_t *env);

/*
**		src/builtins.c
*/

int					check_builtins(char *cmd);
void				do_builtins(char ***final, t_t **env, char **input);

/*
**		src/list_tools.c
*/

char				**env_to_array(t_t *env);
char				**list_to_array(t_list *alst);
void				free_env(t_t **env);
char				*ft_lstsearch(t_t *env, char *to_search);

/*
**		src/list_tools2.c
*/

void				free_red_list(t_red **red);
void				free_ast(t_ast **ast);
int					e2(t_red **red, t_red **tail);
int					e(char **str, char **temp, int f);

/*
**		src/expansions.c
*/

void				its_just_me(char **tmp, char **teemp, int *i, char *tab);
void				expansions(char ***tab, t_t *env);

/*
**		src/all_about_pipes.c
*/

void				manage_fds(int f);
int					manage_pipes(t_cmd *lst);

/*
**		src/exec_tools.c
*/

void				check_perm(char *path);
void				free_cmd_list(t_cmd **lst);
char				*get_full_path(char *cmd, t_t *env);

/*
**		src/exec_red.c
*/

int					get_left_fd(char *cmd, int i);
char				*ft_herdoc(t_red *red);
int					do_redirections(t_red *red);

/*
**		src/builtins/
*/

void				ft_cd(char **tab, t_t **env);
void				ft_echo(char **str);
void				ft_env(t_t *env);
void				ft_exit(char ***final, t_t **env, char **input);
void				ft_setenv(t_t **env, char **final);
void				ft_unsetenv(t_t **env, char **final);

#endif
