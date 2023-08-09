/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:38:55 by apiloian          #+#    #+#             */
/*   Updated: 2023/04/01 19:38:55 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_i(t_pipex *pipex, int i)
{
	if (i == 2)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->fd[i - 2][1], STDOUT_FILENO);
	}
	else if (i == pipex->cmds - 1)
	{
		i--;
		dup2(pipex->outfile, STDOUT_FILENO);
		dup2(pipex->fd[i - 2][0], STDIN_FILENO);
	}
	else
	{
		dup2(pipex->fd[i - 3][0], STDIN_FILENO);
		dup2(pipex->fd[i - 2][1], STDOUT_FILENO);
	}
}

void	piping(t_pipex *pipex, char **argv, char **env, int i)
{
	char	**args;
	char	*path;

	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		opening(pipex, 5, argv);
		args = ft_split(argv[i], ' ');
		path = xx_path(pipex, args[0], env);
		check_i(pipex, i);
		closing(pipex);
		execve(path, args, env);
	}
}

void	pip(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmds - 1)
		pipe(pipex->fd[i++]);
}

void	ft_pipe(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		i;

	i = 2;
	pipex.cmds = argc - 1;
	pip(&pipex);
	while (i < pipex.cmds)
		piping(&pipex, argv, env, i++);
	closing(&pipex);
	while (wait(NULL) != -1)
		;
}
