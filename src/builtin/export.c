/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/15 18:20:51 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_plus(char *key)
{
	char	*plus;

	plus = ft_strrchr(key, '+');
	if (plus == NULL)
		return (0);
	if (plus[0] == '+')
	{
		plus[0] = '\0';
		return (1);
	}
	else
		return (0);
}

void	for_export(t_data *data, char *line)
{
	t_env	*lst;
	char	**keyvalue;
	int		flag;
	char	*tmp;

	flag = 0;
	lst = data->env_lst;
	keyvalue = env_split(line, '=');
	if (check_plus(keyvalue[0]))
		flag = 1;
	while (lst)
	{
		if (ft_strncmp(lst->key, keyvalue[0], ft_strlen(keyvalue[0])) == 0
			&& ft_strncmp(lst->key, keyvalue[0], ft_strlen(lst->key)) == 0)
		{
			if (flag == 0)
			{
				free(lst->val);
				lst->val = NULL;
				lst->val = ft_strdup(keyvalue[1]);
			}
			else
			{
				tmp = lst->val;
				lst->val = NULL;
				lst->val = ft_strjoin(tmp, keyvalue[1]);
				free(tmp);
			}
			free2d(keyvalue);
			return ;
		}
		lst = lst->next;
	}
	env_addback(&data->env_lst, env_new(keyvalue[0], keyvalue[1]));
	free(keyvalue);
}

void	export(t_data *data, t_parse *pars)
{
	int		i;
	char	**keyvalue;

	i = 1;
	if (pars->cmd[1] == NULL)
	{
		export_env(data->env_lst);
		return ;
	}
	keyvalue = env_split(pars->cmd[i], '=');
	i = 1;
	while (pars->cmd[i])
	{
		if (valid_variable_name(keyvalue[0]) == 0)
		{
			free2d(keyvalue);
			return ;
		}
		for_export(data, pars->cmd[i]);
		i++;
	}
	free2d(keyvalue);
}
