/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:37:19 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/01 15:53:54 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void print2d_expo(t_env *enw)
{
	while (enw)
	{
		if (enw->key == NULL)
			return ;
		printf("declare -x %s=\"%s\"\n", enw->key, enw->val);
		enw = enw->next;
	}
}
static void	export_env(t_data *data)
{
	print2d_expo(data->env_lst);
}
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
void Val_To_ExVar(t_env *lst, const char *value)
{
	int i = 0;
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

// void add_Upd_Var(t_env **env, char *key, char *value)
// {
// 	while (*env)
// 	{
//         if (ft_strncmp((*env)->key, key, ft_strlen(key)) == 0)
// 		{
//             free((*env)->val);
//             (*env)->val = ft_strdup(value);
//             return;
//         }
//        	env = &(*env)->next;
// 	}
// 	t_env *new = (t_env *)malloc(sizeof(t_env));
//     if (!new)
//         return;
//     new->key = ft_strdup(key);
//     new->next = NULL;
//     *env = new;
// 	new->key = ft_strdup(key);
// 	if (value == NULL)
// 		new->val = ft_strdup("");
// 	else
// 	new->val = ft_strdup(value);
// 	new->key = NULL;
// 	new->val = NULL;
// 	new->next = NULL;
// }
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
	Val_To_ExVar(lst, pars->cmd[1]);
	// add_Upd_Var(&data->env_lst, str[0], str[1]);
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
	if (str[1] == NULL)
		lst->val = ft_strdup("");
	else
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
	t_env	*lst;

	i = 0;
	lst = data->env_lst;
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
