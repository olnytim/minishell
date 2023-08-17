/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:23 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/16 18:02:21 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define MINISHELL "\e[1;31mminishell\033[0m "
#define NO_CMD "command not found: %s\n"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <limits.h>

#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_env
{
	char *key;
	char *val;
	struct s_env *next;
} t_env;

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
	char **cmd;
	char **operator;
	char **file;
	char **lim;
	int fd;
	t_tig *t_tig;
	struct s_parse *next;
	struct s_parse *prev;
} t_parse;

typedef struct s_data
{
	char **env;
	char *path;
	char *join_path;
	char **cmd_path;
} t_data;

void ft_prompt(void);

void init(t_data *data);

char *find_path(char **env);

char *x_path(t_data *data, char *argv);

void scan_env(char **envp, t_data *data);

int check_builtin(char **args);

t_parse *parsing(char *line);

int args_split(char *line, t_parse *split, int i, int e);

t_parse *smart_split(char *line);

void	ft_lstadd_back_shell(t_parse **lst, t_parse *new);

void error_parsing(void);

void printLinkedList(t_env *head);

void ft_pipe(int argc, char argv, char env);

void print2d(char **arr);

//   BUILTINS  //
void echo(char **args);
// void cd(char **args);
void pwd(void);
//       //

#endif