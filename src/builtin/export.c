/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/08/28 12:36:15 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_data *data, t_parse *pars)
{
	t_env	*lst;
	t_env	*new;
	char	**str;
	
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	lst = data->env_lst;
	str = ft_split(pars->cmd[1], '=');
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
	if (pars->cmd == NULL)
		return ;
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



