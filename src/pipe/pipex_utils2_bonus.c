/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:41:10 by apiloian          #+#    #+#             */
/*   Updated: 2023/04/01 19:41:10 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*search_path(char **env)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = 0;
	while (env[i])
	{
		if (*env[i] == 'P')
		{
			if (!(ft_strncmp_p(path, env[i], 5)))
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

char	*xx_path(t_pipex *pipex, char *argv, char **env)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strncmp(argv, "unset", 5) == 0
		&& ft_strncmp(argv, "unset", ft_strlen(argv)) == 0)
		return (argv);
	if (ft_strncmp(argv, "export", 6) == 0
		&& ft_strncmp(argv, "export", ft_strlen(argv)) == 0)
		return (argv);
	if (ft_strncmp(argv, "exit", 4) == 0
		&& ft_strncmp(argv, "exit", ft_strlen(argv)) == 0)
		return (argv);
	if (access(argv, X_OK) == 0)
		return (argv);
	pipex->path = search_path(env);
	pipex->cmd_path = ft_split_p(pipex->path, ':');
	while (pipex->cmd_path[i])
	{
		pipex->cmd_path[i] = ft_strjoin_p(pipex->cmd_path[i], "/");
		pipex->cmd_path[i] = ft_strjoin_p(pipex->cmd_path[i], argv);
		if (access(pipex->cmd_path[i], X_OK) == 0)
		{
			path = pipex->cmd_path[i];
			return (path);
		}
		i++;
	}
	write(1, "command not found", 18);
	printf(": %s\n", argv);
	exit(0);
}

void	opening(t_pipex *pipex, int argc, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror("");
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror("");
		exit(0);
	}
}

void	closing(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmds - 1)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
	close(pipex->infile);
	close(pipex->outfile);
}
