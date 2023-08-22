/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/08/22 12:56:41 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int only_export(t_data *data)
// {
//     data->env = join_key_and_val(data->env_lst);
// }

// int var_check_name(t_data *data, int *res)
// {
//     int     i;
//     t_env   *lst;
    
//     lst = data->env_lst;
//     i = -1;
//     while (lst->val[++i])
//     {
//         if (!(i == 0 && (lst->val[0] == 0 || lst->val[0] >= 'a'
//             && lst->val[0] <= 'z' || lst->val[0] >= 'A' && lst->val[0] <= 'Z'))
//             return (1);
//         else if (((lst->val[i] >= 'a' && lst->val[i] <= 'z' || lst->val[i] >= 'A' && lst->val[i] <= 'Z')
//                     || (lst->val[i] >= '0' && lst->val[i] <= '9' || lst->val[i] == '_')))
//             return (1);
//         else 
//             *res = 1;
//             return (1);
//     }
//     return (0);
// }

// int export_arg(t_data *data, t_parse *pars, int *j, int i)
// {
//     t_env   *lst;

//     if (pars->cmd[i][0] != '=' && ft_strchr(pars->cmd[i], '=') != 0)
        
// }

void	export(t_data *data, t_parse *pars)
{
	t_env	*lst;
	t_env	*new;
	char	**str;
	
	if (pars->cmd == NULL)
		return ;
	lst = data->env_lst;
	while (lst && lst->next)
		lst = lst->next;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	str = ft_split(pars->cmd[1], '=');
	if (!str[0] || !str[1])
	{
		free(new);
		return;
	}
	lst->key = ft_strdup(str[0]);
	lst->val = ft_strdup(str[1]);
	if (check_export(data, pars)== 0)
	{
		write(2, "error\n", 6);
		exit(0);
	}
	new->key = NULL;
	new->val = NULL;
	new->next = NULL;
	if (!data->env_lst)
        data->env_lst = new;
	else 
        lst->next = new;
	printlinkedlist(data->env_lst);
	free(str);
}

int	check_export(t_data *data, t_parse *pars)
{
	t_env	*lst;
	
	if (pars->cmd == NULL)
		return(0);
	lst = data->env_lst;
	while (lst->next && ft_strncmp(lst->key, pars->cmd[1], ft_strlen(pars->cmd[1]))!= 0)
	{
		if (lst->next && ft_strncmp(lst->next->key, pars->cmd[1], ft_strlen(pars->cmd[1]))== 0)
		{
			return (0);
		}
	}
	return (1);
}

