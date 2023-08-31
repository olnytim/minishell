/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/31 17:24:08 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child(t_parse *input, t_data *data)
{
	int	status;

	status = ft_redirect(input);
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigline);
	if (fork() == 0)
	{
		if (!*input->cmd)
			exit(EXIT_FAILURE);
		if (!data->path)
		{
			printf("ebash: %s: No such file or directory\n", input->cmd[0]);
			exit(EXIT_FAILURE);
		}
		ft_redirect_dup(input, status);
		data->join_path = x_path(data, input->cmd[0]);
		execve(data->join_path, input->cmd, data->env);
	}
	while (wait(NULL) != -1)
		;
}

void	conditions(t_parse *input, t_data *data)
{
	if (input)
	{
		if (check_pipe(input))
			ft_pipe(struct_to2arr(input), data->env, input, data);
		else if (check_builtin_with_redirect(input, data) == 1)
		{
		}
		else
			child(input, data);
	}
}

void	init(t_data *data)
{
	char	*str;
	t_parse	*input;

	while (1)
	{
		sig_event_loop();
		str = readline(MINISHELL);
		if (!str)
		{
			printf("\n\033[1A\033[6Cexit\n");
			exit(EXIT_SUCCESS);
		}
		input = parsing(str);
		data->env = join_key_and_val(data->env_lst);
		data->path = find_path(data->env);
		conditions(input, data);
		unlink("heredoc");
		data->join_path = NULL;
		if (*str)
			add_history(str);
		free(str);
		free2d(data->env);
	}
}
