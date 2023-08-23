/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/08/23 19:30:46 by vfedorov         ###   ########.fr       */
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
			// printlinkedlist(data->env_lst);
			return ;
		}
		lst = lst->next;
	}
	if (pars->cmd == NULL)
		return ;
	lst->key = ft_strdup(str[0]);
	new->key = NULL;
	new->val = NULL;
	new->next = NULL;
	if (!data->env_lst)
        data->env_lst = new;
	else 
        lst->next = new;
	free(str);
}

// int	check_export(t_data *data, char *str)
// {
// 	t_env	*lst;
	
// 	if (str == NULL)
// 		return(0);
// 	lst = data->env_lst;
// 	while (lst->next)
// 	{
// 		if (lst->next && ft_strncmp(lst->next->key, str, ft_strlen(str))== 0)
// 		{
// 			return (0);
// 		}
// 		lst = lst->next;
// 	}
// 	return (1);
// }

