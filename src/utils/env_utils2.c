/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:50:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
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

void	check_shlvl(t_env **head)
{
	t_env	*lst;

	lst = *head;
	while (lst)
	{
		if (lst->key[0] == 'S' && ft_strncmp(lst->key, "SHLVL", 5) == 0
			&& ft_strncmp(lst->key, "SHLVL", ft_strlen(lst->key)) == 0)
			return ;
		lst = lst->next;
	}
	env_addback(head, env_new(ft_strdup("SHLVL"), ft_strdup("1"), 0));
}

char	**join_key_val_cont(char **arr, int i, t_env *lst)
{
	char	*tmp;

	arr[i] = ft_strjoin(lst->key, "=");
	tmp = ft_strdup(arr[i]);
	free(arr[i]);
	arr[i] = ft_strjoin(tmp, lst->val);
	free(tmp);
	return (arr);
}
