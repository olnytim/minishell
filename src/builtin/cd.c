/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:07:13 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/15 18:16:41 by vfedorov         ###   ########.fr       */
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
		tmp = str;
		str = ft_strjoin(tmp, pointer);
		free(tmp);
		for_export(data, str);
		free(str);
	}
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

void	minus(t_data *data)
{
	char	*min;

	min = whum_find(data, "OLDPWD");
	if (!(chdir(min)))
	{
		pwd();
		return ;
	}
	else
		printf ("ebash: cd: OLDPWD is not set\n");
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
		minus(data);
	else if (pars->cmd[1][0] == '~')
		tilda_main(data, pars, joi);
	else if (valid_dir(pars->cmd[1]) == -1)
		printf("cd: %s: No such file or directory\n", pars->cmd[1]);
	else
		norm_cd(data, pars, old, new);
	free(joi);
}
