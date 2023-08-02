/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:04:30 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/01 19:30:53 by apiloian         ###   ########.fr       */
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

void	scan_env(char **envp, t_data *data)
{
	char	*str;
	char	**key_val;
	t_env	*head;

	data->env = malloc(sizeof(t_env));
	head = data->env;
	while (*envp)
	{
		str = *envp;
		data->env->next = malloc(sizeof(t_env));
		key_val = ft_split(str, '=');
		data->env->key = key_val[0];
		data->env->val = key_val[1];
		free(key_val);
		data->env = data->env->next;
		envp++;
	}
	data->env = head;
}

// char	**create_2d(t_data *data)
// {
// 	char	**env;

// 	return (env);
// }
