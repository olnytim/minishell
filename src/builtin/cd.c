/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:07:13 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/12 22:12:39 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_var(t_data	*data, char *line, char *pointer)
{
	t_env	*lst;
	char	*str;
	char	*tmp;

	lst = data->env_lst;
	while (ft_strncmp(lst->key, line,
			ft_strlen(lst->key)) != 0
		&& ft_strncmp(lst->key, line,
			ft_strlen(line)) != 0)
		lst = lst->next;
	if (ft_strncmp(lst->key, line,
			ft_strlen(lst->key)) == 0
		&& ft_strncmp(lst->key, line,
			ft_strlen(line)) == 0)
	{
		str = ft_strjoin(line, "=");
		tmp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmp, pointer);
		free(tmp);
		for_export(data, str);
	}
}

char	*find_user(t_data *data)
{
	t_env	*lst;

	lst = data->env_lst;
	while (ft_strncmp(lst->key, "USER=",
			ft_strlen(lst->key)) != 0
		&& ft_strncmp(lst->key, "USER=",
			ft_strlen("USER=")) != 0)
		lst = lst->next;
	return (lst->val);
}

void	just_cd(t_data *data, char *user, char *old, char *new)
{
	// char	*join;

	getcwd(old, PATH_MAX);
	// join = ft_strjoin("/Users/", user);
	chdir(user);
	find_var(data, "OLDPWD", old);
	getcwd(new, PATH_MAX);
	find_var(data, "PWD", new);
}

void	check_line(char *line)
{
	int	i;

	i = 0;
	while (line)
	{
		if ((line[i] >= 33 && line[i] <= 45)
			|| (line[i] >= 48 && line[i] <= 64))
		{
			printf("cd: %s: No such file or directory\n", line);
			return ;
		}
	}
}

void	cd(t_data *data, t_parse *pars)
{
	char	old[PATH_MAX];
	char	new[PATH_MAX];
	char	*user;
	char	*valid;
	char	*joi;

	user = find_user(data);
	if (pars->cmd[1] == NULL)
		just_cd(data, user, old, new);
	else if (pars->cmd[1][0] == '~')
	{
			joi = ft_strjoin("/Users/", user);
			valid = ft_strjoin(joi, pars->cmd[1] + 1);
			if (valid_dir(valid) == -1)
			{
				printf("cd: %s: No such file or directory\n", pars->cmd[1]);
				return ;
			}
			else 
				just_cd(data, valid, old, new);	
	}
	else if (valid_dir(pars->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", pars->cmd[1]);
		return ;
	}
	else
		norm_cd(data, pars, old, new);
}
