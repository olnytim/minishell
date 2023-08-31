/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/08/31 12:14:41 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	export(t_data *data, t_parse *pars)
// {
// 	t_env	*lst;
// 	t_env	*new;
// 	char	**str;
// 	int		i;
// 	int		cnt;

// 	i = 1;
// 	cnt = 0;
// 	new = (t_env *)malloc(sizeof(t_env) * cnt + 1);
// 	if (!new)
// 		return ;
// 	while (pars->cmd[i])
// 	{
// 		cnt++;
// 	i = 1;
// 	if (pars->cmd == NULL)
// 		return ;
// 	while (pars->cmd[i])
// 	{
		
// 		lst = data->env_lst;
// 		str = env_split(pars->cmd[i], '=');
// 		if (!*str || !str)
// 		{
// 			free(new);
// 			return;
// 		}
// 		while (lst && lst->next)
// 		{
// 			if (lst->next && ft_strncmp(lst->key, str[0], ft_strlen(str[0]))== 0)
// 			{
// 				free(lst->val);
// 				lst->val = ft_strdup(str[1]);
// 				return ;
// 			}
// 			{
// 				free(lst->val);
// 				lst->val = ft_strdup(str[1]);
// 				return ;
// 			}
// 			lst = lst->next;
// 		}
// 		lst->next = new;
// 		new->key = NULL;
// 		new->val = NULL;
// 		lst->key = ft_strdup(str[0]);
// 		lst->val = ft_strdup(str[1]);
// 		lst->next = new;
// 		new->next = NULL;
// 		i++;
// 	}
// 		i++;
// 	}
// 	free(str);
// }



void	for_export(t_data *data, char *line)
{
	t_env	*lst;
	t_env	*new;
	char	**str;
	

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	lst = data->env_lst;
	str = env_split(line, '=');
	dprintf(1, "%s\n", line);
	if (!str[0] || !str[1])
	{
		free(new);
		return;
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
	// printLinkedList(data->env_lst);
	free(str);
}


void	export(t_data *data, t_parse *pars)
{
	int	i;

	i = 1;
	if (pars->cmd[1] == NULL)
		return ;
	while (pars->cmd[i])
	{
		for_export(data, pars->cmd[i]);
		i++;
	}
}
//somet
