/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:23:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/01 18:42:31 by valeriafedo      ###   ########.fr       */
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
	arr[i] = NULL;
	return (arr);
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

void	scan_env(char **envp, t_data *data)
{
	char	**key_val;
	t_env	*head;
	t_env	*env;

	env = malloc(sizeof(t_env));
	head = env;
	while (*envp)
	{
		key_val = env_split(*envp, '=');
		env->next = malloc(sizeof(t_env));
		key_val = shlvl(key_val);
		env->key = key_val[0];
		env->val = key_val[1];
		env = env->next;
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

void	free2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	printLinkedList(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("Key: %s, Val: %s\n", current->key, current->val);
		current = current->next;
	}
}

