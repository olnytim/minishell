/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:23:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/08 14:30:11 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_size(t_env *lst)
{
	size_t	counter;

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
		arr[i] = ft_strjoin(lst->key, "=");
		arr[i] = ft_strjoin(arr[i], lst->val);
		lst = lst->next;
		++i;
	}
	arr[i] = NULL;
	return (arr);
}

void	scan_env(char **envp, t_data *data)
{
	char	*str;
	char	**key_val;
	t_env	*head;
	t_env	*env;

	env = malloc(sizeof(t_env));
	head = env;
	while (*envp)
	{
		str = *envp;
		env->next = malloc(sizeof(t_env));
		key_val = ft_split(str, '=');
		env->key = key_val[0];
		env->val = key_val[1];
		env = env->next;
		envp++;
	}
	env = head;
	data->env_lst = env;
	// printlinkedlist(data->env_lst);
	data->env = join_key_and_val(env);
	// print2d(data->env);
	// exit(0);
}

void	printlinkedlist(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("Key: %s, Val: %s\n", current->key, current->val);
		current = current->next;
	}
}

void	print2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
