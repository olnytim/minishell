/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/01 18:42:16 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	val_to_exvar(t_env *lst, const char *value)
{
	int	i;

	i = 0;
	while (lst->key[i])
	{
		if (lst->key[i] == '+' && lst->key[i + 1] == '\0')
		{
			lst->key[i] = '\0';
			lst->val = ft_strjoin(lst->val, value);
		}
		i++;
	}
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

void	for_export(t_data *data, char *line, t_parse *pars)
{
	t_env	*lst;
	char	**keyvalue;

	lst = data->env_lst;
	keyvalue = env_split(line, '=');
	val_to_exvar(lst, pars->cmd[1]);
	while (lst && lst->next)
	{
		if (lst->next && ft_strncmp(lst->key, keyvalue[0],
				ft_strlen(keyvalue[0])) == 0)
		{
			free(lst->val);
			lst->val = ft_strdup(keyvalue[1]);
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
