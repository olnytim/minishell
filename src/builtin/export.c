/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:18:39 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:18:50 by vfedorov         ###   ########.fr       */
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

int	find_equal(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	for_export_cont(int flag, t_env *lst, char **keyvalue)
{
	char	*tmp;

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
	g_exit_code = 0;
}

void	for_export(t_data *data, char *line)
{
	t_env	*lst;
	char	**keyvalue;
	int		flag;
	int		eq;

	flag = 0;
	lst = data->env_lst;
	if (find_equal(line, '='))
		eq = 1;
	else
		eq = 0;
	keyvalue = env_split(line, '=');
	if (check_plus(keyvalue[0]))
		flag = 1;
	while (lst)
	{
		if (ft_strncmp(lst->key, keyvalue[0], ft_strlen(keyvalue[0])) == 0
			&& ft_strncmp(lst->key, keyvalue[0], ft_strlen(lst->key)) == 0)
			return (for_export_cont(flag, lst, keyvalue));
		lst = lst->next;
	}
	env_addback(&data->env_lst, env_new(keyvalue[0], keyvalue[1], eq));
	free(keyvalue);
	g_exit_code = 0;
}

void	export(t_data *data, t_parse *pars)
{
	int		i;
	char	**keyvalue;
	char	*tmp;

	i = 1;
	if (pars->cmd[1] == NULL)
		return (export_env(data->env_lst));
	tmp = ft_strdup(pars->cmd[i]);
	keyvalue = env_split(tmp, '=');
	i = 1;
	while (pars->cmd[i])
	{
		if (valid_variable_name(keyvalue[0]) == 0)
		{
			free(tmp);
			free2d(keyvalue);
			g_exit_code = 1;
			return ;
		}
		for_export(data, pars->cmd[i++]);
	}
	free2d(keyvalue);
	free(tmp);
}
