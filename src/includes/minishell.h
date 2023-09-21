/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:21:42 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/21 20:19:28 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL  "\e[1;31m5051\033[0m "
# define NO_CMD     "ebash: %s: command not found\n"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>

# include "../../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*val;
	int				flag;
	struct s_env	*next;
}	t_env;

typedef struct s_tig
{
	int	i_op;
	int	i_fl;
	int	i_lm;
	int	i_cmd;
}	t_tig;

typedef struct s_dol
{
	char	*buf;
	char	*str;
	int		flag;
	char	q;
}	t_dol;

typedef struct s_parse
{
	char			**cmd;
	char			**operator;
	char			**file;
	char			**lim;
	int				fd_in;
	int				fd_out;
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

int		g_exit_code;

void	init(t_data *data);

char	*find_path(char **env);

char	*x_path(t_data *data, char *argv);

int		ft_env_size(t_env *head);

char	**shlvl(char **key_val);

void	check_shlvl(t_env **head);

void	scan_env(char **envp, t_data *data);

int		check_builtin(t_parse *cmd, t_data *data);

int		check_builtin_with_redirect(t_parse *cmd, t_data *data);

int		builtin_cmp(char *cmd);

int		args_split(char *line, t_parse *split, int i, int e);

int		count_buf(int i, int w, char *line);

int		count_cmd(int i, int w, char *line);

int		count_file(int i, int w, char *line);

int		count_oper(int i, int w, char *line);

int		count_lim(int i, int w, char *line);

t_parse	*error(int e);

t_parse	*parsing(char *line, t_env *env);

t_parse	*smart_split(char *line);

int		count_wr_dol_buf(char *val);

char	*join_dol(char *str, char *buf, int j);

char	*file_lim_quotes(char *arg, int *i, int j);

void	quote_handle(char *line, char *buf, int *i, int *j);

char	*ft_strjoin_nl(char *str1, char *str2);

char	*desipher_dollar(char *line, t_env *env, int i, int j);

char	*fill_proc_buf(char *buf);

char	**join_key_and_val(t_env *head);

int		desipher_dollar_1(char *line, int i);

void	ft_pipe(char **argv, char **env, t_parse *cmd, t_data *data);

int		ft_parse_size(t_parse *lst);

char	desipher_dollar_cont_1(char *line, char q, int *flag, int *i);

char	*fill_dol_buf(char *buf, char *val, int i, int j);

char	*join_2d_arr(char **arr);

int		check_pipe(t_parse *input);

char	**struct_to2arr(t_parse *lst);

int		ft_redirect(t_parse *lst);

int		ft_redirect_in(t_parse *lst);

int		ft_redirect_heredoc(t_parse *lst);

int		ft_redirect_out(t_parse *lst);

int		ft_redirect_out_append(t_parse *lst);

void	ft_redirect_dup(t_parse *lst, int status);

void	ft_redirect_cmp(t_parse *lst, int *status);

void	print_linked_list(t_env *head);

void	print2d(char **arr);

void	ft_lstadd_back_shell(t_parse **lst, t_parse *new);

void	error_parsing(void);

void	free2d(char **arr);

char	**env_split(char *str, char lim);

void	sig_event_loop(void);

void	ft_next_line(int sig);

void	ft_sigquit(int sig);

void	ft_sigline(int sig);

void	ft_sigempty(int sig);

void	free_input(t_parse *splited, t_parse *input);

int		ft_lstsize_t_parse(t_parse *lst);

int		ft_isdir(const char *name);

void	sig_ex(char *str);

void	init_cont_1(t_data *data, t_parse *input, char *str);

t_parse	*duble_pointers(t_parse *input);

void	conditions(t_parse *input, t_data *data);

void	env_addback(t_env **head, t_env *to_push);

t_env	*env_new(char *key, char *value, int flag);

char	**join_key_val_cont(char **arr, int i, t_env *lst);

//			BUILTINS		//
void	echo(char **args);
void	unset(t_data *data, t_parse *pars);
void	export(t_data *data, t_parse *pars);
int		check_export(t_data *data, char *str);
int		ft_exit(t_parse *input);
int		unset_forchar(int symbol);
void	unset_valid_variable_name(char *var);
int		forchar(int symbol);
int		valid_variable_name(char *var);
void	export_env(t_env *head);
void	cd(t_data *data, t_parse *pars);
void	for_export(t_data *data, char *line);
void	pwd(void);
void	env(t_data *data, t_parse *pars);
int		valid_dir(char *path);
void	norm_cd(t_data *data, t_parse *pars, char *old, char *new);
void	find_var(t_data	*data, char *line, char *pointer);
int		sravnim(char *str1, char *str2);
int		tilda(t_parse *pars, char *valid);
char	*whum_find(t_data *data, char *whum);
void	tilda_main(t_data *data, t_parse *pars, char *joi);
void	just_cd(t_data *data, char *user, char *old, char *new);
void	exit_message_for_ebash(char *cmd);
int		heredoc_skip(char *line, int i, t_dol *dol, int *j);

//							//

#endif