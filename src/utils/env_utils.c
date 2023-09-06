/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:23:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/04 17:15:55 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_size(t_env *head)
{
	size_t	counter;
	t_env	*lst;

	lst = head;
	counter = 0;
	while (lst)
	{
		lst = lst->next;
		++counter;
	}
	return (counter);
}

char	**join_key_and_val(t_env *head)
{
	char	**arr;
	char	*tmp;
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
		arr[i] = ft_strjoin(lst->key, "=");
		tmp = ft_strdup(arr[i]);
		free(arr[i]);
		arr[i] = ft_strjoin(tmp, lst->val);
		free(tmp);
		lst = lst->next;
		++i;
	}
	return (arr[i] = NULL, arr);
}

char	**shlvl(char **key_val)
{
	char	*tmp;
	int		i;

	if (key_val[0][0] == 'S' && ft_strncmp(key_val[0], "SHLVL", 5) == 0
		&& ft_strncmp(key_val[0], "SHLVL", ft_strlen(key_val[0])) == 0)
	{
		if (!key_val[1])
			key_val[1] = ft_strdup("1");
		else
		{
			tmp = ft_strdup(key_val[1]);
			free(key_val[1]);
			i = ft_atoi(tmp) + 1;
			key_val[1] = ft_itoa(i);
			free(tmp);
		}
	}
	return (key_val);
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

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->key = key;
	new->val = value;
	return (new);
}

void	env_addback(t_env **head, t_env *to_push)
{
	if (head)
	{
		if(*head)
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
		key_val = shlvl(key_val);
		env_addback(&head, env_new(key_val[0], key_val[1]));
		free(key_val);
		envp++;
	}
	data->env_lst = head;
}

char	**env_split(char *str, char lim)
{
	char	**split;
	int		i;

	split = malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == lim)
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	split[0] = ft_strdup(str);
	split[1] = ft_strdup(str + i + 1);
	split[2] = NULL;
	return (split);
}
