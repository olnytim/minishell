/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:23 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/28 12:35:20 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL  "\e[1;31mebash\033[0m "
# define NO_CMD     "command not found: %s\n"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <limits.h>
# include <signal.h>

# include "../../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_tig
{
	int i_op;
	int i_fl;
	int i_lm;
	int	i_cmd;
	int	**q_op;
} t_tig;

typedef struct s_parse
{
	char			**cmd;
	char			**operator;
	char			**file;
	char			**lim;
	int				fd;
	t_tig			*t_tig;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_data
{
	char	**env;
	char	*path;
	char	*join_path;
	char	**cmd_path;
	t_env	*env_lst;
}	t_data;

void	init(t_data *data);

char	*find_path(char **env);

char	*x_path(t_data *data, char *argv);

void	scan_env(char **envp, t_data *data);

int		check_builtin(t_parse *cmd, t_data *data);

int		check_builtin_with_redirect(t_parse *cmd, t_data *data);

int		builtin_cmp(char *cmd);

int		args_split(char *line, t_parse *split, int i, int e);

t_parse	*error(int e);

t_parse *parsing(char *line);

t_parse *smart_split(char *line);

t_parse	*smart_split(char *line);

char	**join_key_and_val(t_env *head);

void	ft_pipe(char **argv, char **env, t_parse *cmd, t_data *data);

int		ft_parse_size(t_parse *lst);

char	*join_2d_arr(char **arr);

char	**struct_to2arr(t_parse *lst);

int		ft_redirect(t_parse *lst);

void	print2d(char **arr);

void	ft_lstadd_back_shell(t_parse **lst, t_parse *new);

void	error_parsing(void);

void	printLinkedList(t_env *head);

void	print2d(char **arr);

void	sig_event_loop(void);

//			BUILTINS		//
void	echo(char **args);
void	unset(t_data *data, t_parse *pars);
void	export(t_data *data, t_parse *pars);
int		check_export(t_data *data, char *str);
void	ft_exit(t_parse *input);
// void	cd(char **args);
void	pwd(void);
void	env(t_data *data);
//							//

#endif