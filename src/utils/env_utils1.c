/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:23:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**join_key_and_val(t_env *head)
{
	char	**arr;
	t_env	*lst;
	size_t	size;
	size_t	i;

	lst = head;
	size = ft_env_size(lst);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (!lst->key)
			break ;
		if (*lst->val)
			arr = join_key_val_cont(arr, i, lst);
		else
			arr[i] = ft_strdup(lst->key);
		lst = lst->next;
		++i;
	}
	return (arr[i] = NULL, arr);
}

t_env	*env_last(t_env *head)
{
	if (head)
	{	
		while (head->next)
			head = head->next;
	}
	return (head);
}

t_env	*env_new(char *key, char *value, int flag)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->key = key;
	new->val = value;
	new->flag = flag;
	return (new);
}

void	env_addback(t_env **head, t_env *to_push)
{
	if (head)
	{
		if (*head)
			env_last(*head)->next = to_push;
		else
			*head = to_push;
	}
}

void	scan_env(char **envp, t_data *data)
{
	char	**key_val;
	t_env	*head;

	head = NULL;
	while (*envp)
	{
		key_val = env_split(*envp, '=');
		if (key_val[0][0] == 'O' && ft_strncmp(key_val[0], "OLDPWD", 6) == 0
		&& ft_strncmp(key_val[0], "OLDPWD", ft_strlen(key_val[0])) == 0)
		{
			env_addback(&head, env_new(ft_strdup("OLDPWD"), ft_strdup("\0"), 0));
			free2d(key_val);
			envp++;
			continue ;
		}
		key_val = shlvl(key_val);
		env_addback(&head, env_new(key_val[0], key_val[1], 0));
		free(key_val);
		envp++;
	}
	check_shlvl(&head);
	data->env_lst = head;
}
