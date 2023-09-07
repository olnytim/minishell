/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:07:13 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/07 21:59:01 by valeriafedo      ###   ########.fr       */
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

void	find_way(t_data *data, char *old)
{
	char	new[PATH_MAX];

	find_var(data, "OLDPWD", old);
	getcwd(new, PATH_MAX);
	find_var(data, "PWD", new);
	
}

void	cd(t_data *data, t_parse *pars)
{
	char	old[PATH_MAX];

	getcwd(old, PATH_MAX);
	chdir(pars->cmd[1]);
	find_way(data, old);
}

