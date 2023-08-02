/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:34:15 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/02 16:46:27 by timelkon         ###   ########.fr       */
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
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_data
{
	t_env	*env;
	char	*path;
	char	*join_path;
	char	**cmd_path;
}	t_data;

void	ft_prompt(void);

void	init(char **envp, t_data *data);

char	*find_path(char **env);

char	*x_path(t_data *data, char *argv);

int		check_builtin(char **args);

int		parsing(char *line);

//			BUILTINS		//
void	echo(char **args);
// void	cd(char **args);
void	pwd(void);
//							//

#endif