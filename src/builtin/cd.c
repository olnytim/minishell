/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:18:25 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:18:54 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_var(t_data	*data, char *line, char *pointer)
{
	t_env	*lst;
	char	*str;
	char	*tmp;

	lst = data->env_lst;
	while (lst->next
		&& ft_strncmp(lst->key, line, ft_strlen(lst->key)) != 0
		&& ft_strncmp(lst->key, line, ft_strlen(line)) != 0)
		lst = lst->next;
	str = ft_strjoin(line, "=");
	tmp = str;
	str = ft_strjoin(tmp, pointer);
	free(tmp);
	for_export(data, str);
	free(str);
}

void	just_cd(t_data *data, char *user, char *old, char *new)
{
	old = getcwd(0, 0);
	chdir(user);
	find_var(data, "OLDPWD", old);
	new = getcwd(0, 0);
	find_var(data, "PWD", new);
	free(old);
	free(new);
	g_exit_code = 0;
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

void	minus(t_data *data, char *str)
{
	char	*min;

	if ((str[1] && str[2]) && (str[1] != '-' || str[1] != '\0'))
	{
		if (str[2] && str[2] != '\0')
		{
			printf("ebash: cd: -%c: invalid option\n", str[1]);
			g_exit_code = 1;
			return ;
		}
	}
	min = whum_find(data, "OLDPWD");
	if (!chdir(min))
	{
		if (str[1] != '-')
			pwd();
		g_exit_code = 0;
		return ;
	}
	else
	{
		printf ("ebash: cd: OLDPWD is not set\n");
		g_exit_code = 1;
	}
}

void	cd(t_data *data, t_parse *pars)
{
	char	*old;
	char	*new;
	char	*user;
	char	*joi;

	old = NULL;
	new = NULL;
	user = whum_find(data, "USER");
	joi = ft_strjoin("/Users/", user);
	if (pars->cmd[1] == NULL)
		just_cd(data, joi, old, new);
	else if (pars->cmd[1][0] == '-')
		minus(data, pars->cmd[1]);
	else if (pars->cmd[1][0] == '~')
		tilda_main(data, pars, joi);
	else if (valid_dir(pars->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", pars->cmd[1]);
		g_exit_code = 1;
	}
	else
		norm_cd(data, pars, old, new);
	free(joi);
}
