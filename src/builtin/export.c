/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/01 14:05:20 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extra(char **str, t_env **new)
{	
	new = (t_env **)malloc(sizeof(t_env));
	if (!new)
		return ;
	if (!str[0] || !str[1])
	{
		free(new);
		return ;
	}
}

void	for_export(t_data *data, char *line, t_parse *pars)
{
	t_env	*lst;
	t_env	*new;
	char	**str;
	int		i;
	
	i = 0;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	lst = data->env_lst;
	str = env_split(line, '=');
	extra(str, &new);
	while (lst->key[i])
	{
		i++;
		if (lst->key[i] == '+' && lst->key[i + 1] == '\0')
		{
			lst->key[i] = '\0';
			lst->val = ft_strjoin(lst->val, pars->cmd[1]);
		}
	}
	while (lst && lst->next)
	{
		if (lst->next && ft_strncmp(lst->key, str[0], ft_strlen(str[0]))== 0)
		{
			free(lst->val);
			lst->val = ft_strdup(str[1]);
			return ;
		}
		lst = lst->next;
	}
	lst->key = ft_strdup(str[0]);
	lst->val = ft_strdup(str[1]);
	new->key = NULL;
	new->val = NULL;
	new->next = NULL;
	if (!data->env_lst)
        data->env_lst = new;
	else 
        lst->next = new;
	free(str);
}

void	export(t_data *data, t_parse *pars)
{
	int	i;
	// t_env	*lst;

	i = 0;
	// lst = data->env_lst;
	if (pars->cmd[1] == NULL)
		return ;
	i = 1;
	while (pars->cmd[i])
	{
		if (ft_strchr(pars->cmd[i], '=')== 0 || ft_isdigit(pars->cmd[i][0]) == 1
			|| pars->cmd[i][0] == '=' || ft_isalpha(pars->cmd[i][0]) == 0)
		{
			write(2, "export: not a valid identifier \n", 32);
			return ;
		}
		for_export(data, pars->cmd[i], pars);
		i++;
	}
}