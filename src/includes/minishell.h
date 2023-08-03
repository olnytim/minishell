/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/08/02 16:34:15 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/02 16:46:27 by timelkon         ###   ########.fr       */
=======
/*   Created: 2023/07/15 19:14:42 by olnytim           #+#    #+#             */
/*   Updated: 2023/08/03 18:03:15 by apiloian         ###   ########.fr       */
>>>>>>> crrips
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
<<<<<<< HEAD
	char			**cmd;
=======
	char			*cmd;
>>>>>>> crrips
	char			*operator;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_data
{
	char	**env;
	char	*path;
	char	*join_path;
	char	**cmd_path;
}	t_data;

void	ft_prompt(void);

void	init(t_data *data);

char	*find_path(char **env);

char	*x_path(t_data *data, char *argv);

void	scan_env(char **envp, t_data *data);

int		check_builtin(char **args);

<<<<<<< HEAD
int		parsing(char *line);
=======
void	printLinkedList(t_env *head);

void	ft_pipe(int argc, char **argv, char **env);

void	print2d(char **arr);
>>>>>>> crrips

//			BUILTINS		//
void	echo(char **args);
// void	cd(char **args);
void	pwd(void);
//							//

#endif