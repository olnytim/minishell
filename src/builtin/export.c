/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/14 22:24:42 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_plus(char *key)
{
	char	*plus;

	plus = ft_strrchr(key, '+');
	if (plus == NULL)
		return (key);
	if (plus[0] == '+')
	{
		plus[0] = '\0';
		return (key);
	}
	else
		return (key);
}

void	for_export(t_data *data, char *line)
{
	t_env	*lst;
	char	**keyvalue;
	int		flag;
	char	*tmp;

	lst = data->env_lst;
	keyvalue = env_split(line, '=');
	if (check_plus(keyvalue[0]) == 0)
		flag = 0;
	while (lst)
	{
		if (ft_strncmp(lst->key, keyvalue[0], ft_strlen(keyvalue[0])) == 0)
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
				lst->val = ft_strjoin(tmp, keyvalue[1]);
				free(tmp);
			}
			return ;
		}
		lst = lst->next;
	}
	env_addback(&data->env_lst, env_new(keyvalue[0], keyvalue[1]));
	// free(keyvalue);
}

void	export(t_data *data, t_parse *pars)
{
	int		i;
	char	**keyvalue;

	i = 1;
	// printf("%s\n", pars->cmd[1]);
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
		printf("%p\n", keyvalue);
		printf("%s\n", keyvalue[0] + 16);
		printf("%p\n", keyvalue[1]);
		i++;
	}
	free2d(keyvalue);
}
