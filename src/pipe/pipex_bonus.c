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

void	check_i(t_pipex *pipex, int i, t_parse *cmd)
{
	if (*cmd->operator && **cmd->operator == '<'
		&& *(*cmd->operator + 1) == '<')
		return ;
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

void	piping(t_pipex *pipex, char **env, int i, t_parse *cmd)
{
	char	**args;
	char	*path;
	int		status;

	sig_event_loop();
	status = ft_redirect(cmd);
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigline);
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		opening(pipex, pipex->argc, pipex->argv);
		args = ft_split_p(pipex->argv[i], ' ');
		path = xx_path(pipex, args[0], env);
		check_i(pipex, i, cmd);
		ft_redirect_dup(cmd, status);
		closing(pipex);
		if (check_builtin(cmd, pipex->data) == 1)
			exit(EXIT_SUCCESS);
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

void	ft_pipe(char **argv, char **env, t_parse *cmd, t_data *data)
{
	t_pipex	pipex;
	int		i;
	int		status;

	pipex.argc = ft_parse_size(cmd) + 3;
	pipex.argv = argv;
	pipex.data = data;
	i = 2;
	pipex.cmds = pipex.argc - 1;
	pip(&pipex);
	while (i < pipex.cmds)
	{
		piping(&pipex, env, i++, cmd);
		cmd = cmd->next;
	}
	closing(&pipex);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	free2d(argv);
}
