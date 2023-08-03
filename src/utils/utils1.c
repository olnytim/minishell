/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:04:30 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/03 18:11:42 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **env)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = 0;
	while (env[i])
	{
		if (*env[i] == 'P')
		{
			if (!(ft_strncmp(path, env[i], 5)))
			{
				path = env[i];
				while (*path != '/')
					path++;
				return (path);
			}
		}
		i++;
	}
	return (0);
}

char	*x_path(t_data *data, char *argv)
{
	int		i;
	char	*path;

	i = 0;
	data->cmd_path = ft_split(data->path, ':');
	while (data->cmd_path[i])
	{
		data->cmd_path[i] = ft_strjoin(data->cmd_path[i], "/");
		data->cmd_path[i] = ft_strjoin(data->cmd_path[i], argv);
		if (access(data->cmd_path[i], X_OK) == 0)
		{
			path = data->cmd_path[i];
			return (path);
		}
		i++;
	}
	printf(NO_CMD, argv);
	exit(EXIT_FAILURE);
}

int	check_builtin(char **args)
{
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		return (pwd(), 1);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		return (echo(args), 1);
	// else if (ft_strncmp(args[0], "cd", 2) == 0)
	// 	return (cd(args), 1);
	return (0);
}


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

char	**join_key_and_val(t_env *lst)
{
	char	**arr;
	size_t	size;
	size_t	i;

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
	data->env = join_key_and_val(env);
}

void	printLinkedList(t_env *head)
{
	t_env *current = head;

	while (current != NULL)
	{
		printf("Key: %s, Val: %s\n", current->key, current->val);
		current = current->next;
	}
}

void	print2d(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
