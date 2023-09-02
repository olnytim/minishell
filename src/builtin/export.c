/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/02 17:14:52 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	val_to_exvar(t_env *lst, const char *value)
{

	printf ("%s\n", value);
	lst->val = ft_strjoin(lst->val, value);
}

void	add_keyvalue_to_env(char **keyvalue, t_env *end)
{
	t_env	*new;

	end->key = ft_strdup(keyvalue[0]);
	if (keyvalue[1] == NULL)
		end->val = ft_strdup("");
	else
	end->val = ft_strdup(keyvalue[1]);
	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	*new = (t_env){0};
	end->next = new;
	free(keyvalue[0]);
	free(keyvalue[1]);
	free(keyvalue);
}

char	*check_plus(char *key)
{
	char *plus;

	plus = ft_strrchr(key, '+');
	if (plus[0] == '+')
	{
		plus[0] = '\0';
		return (key);
	}
	else
		return (key);
}

void	for_export(t_data *data, char *line, t_parse *pars)
{
	t_env	*lst;
	char	**keyvalue;
	int		flag;
	
	lst = data->env_lst;
	keyvalue = env_split(line, '=');
	if (check_plus(keyvalue[0]) == 0)
		flag = 0;
	else
		flag = 1;
	printf ("%s\n", keyvalue[0]);
	while (lst && lst->next)
	{
		if (lst->next && ft_strncmp(lst->key, keyvalue[0], ft_strlen(keyvalue[0])) == 0)
		{
			if (flag == 0)
			{
				free(lst->val);
				lst->val = ft_strdup(keyvalue[1]);
			}
			else
			{
				printf ("%s\n", pars->cmd[1]);
				val_to_exvar(lst, keyvalue[1]);
			}
			return ;
		}
		lst = lst->next;
	}
	add_keyvalue_to_env(keyvalue, lst);
}

void	export(t_data *data, t_parse *pars)
{
	int	i;

	i = 0;
	if (pars->cmd[1] == NULL)
		export_env(data);
	i = 1;
	while (pars->cmd[i])
	{
		if (valid_variable_name(pars->cmd[i]) == 0)
			return ;
		for_export(data, pars->cmd[i], pars);
		i++;
	}
}
