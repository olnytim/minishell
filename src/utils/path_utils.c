/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:04:30 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
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

void	check_dir(char *argv)
{
	if (ft_strncmp(argv, ".", 1) == 0 && ft_strlen(argv) == 1)
	{
		printf("ebash: %s: Eto nam ne zadavali\n", argv);
		exit(2);
	}
	if (ft_isdir(argv) == 0)
	{
		printf("ebash: %s: is a directory\n", argv);
		exit(126);
	}
}

char	*x_path(t_data *data, char *argv)
{
	int		i;
	char	*path;

	i = 0;
	if (!data->path)
		return (NULL);
	data->cmd_path = ft_split(data->path, ':');
	check_dir(argv);
	if (access(argv, X_OK) == 0)
		return (argv);
	while (data->cmd_path && data->cmd_path[i] && *argv)
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
	ft_putstr_fd("ebash: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
