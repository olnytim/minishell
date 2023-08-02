/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:14:42 by olnytim           #+#    #+#             */
/*   Updated: 2023/08/01 19:34:39 by apiloian         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
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

//			BUILTINS		//
void	echo(char **args);
// void	cd(char **args);
void	pwd(void);
//							//

#endif