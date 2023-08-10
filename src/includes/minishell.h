/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:31:13 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/10 13:00:03 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL  "\e[1;31mminishell\033[0m "
# define NO_CMD     "command not found: %s\n"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <limits.h>

# include "../../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_parse
{
	char			**cmd;
	char			*operator;
	char			*file;
	char			*lim;
	int				fd;
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

void	ft_prompt(void);

void	init(t_data *data);

char	*find_path(char **env);

char	*x_path(t_data *data, char *argv);

void	scan_env(char **envp, t_data *data);

int		check_builtin(t_parse *lst, t_data *data);

char	**join_key_and_val(t_env *head);

void	ft_pipe(int argc, char **argv, char **env);

int		ft_parse_size(t_parse *lst);

char	*join_2d_arr(char **arr);

char	**struct_to2arr(t_parse *lst);

void	ft_redirect(t_parse *lst);

void	printlinkedlist(t_env *head);

void	print2d(char **arr);

//			BUILTINS		//
void	echo(char **args);
void	unset(t_data *data, char **argv);
// void	cd(char **args);
void	pwd(void);
void	env(t_data *data);
//							//

#endif