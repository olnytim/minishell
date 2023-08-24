/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/24 16:51:19 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child(t_parse *input, t_data *data)
{
	if (!ft_redirect(input))
	{
		if (!*input->cmd)
			exit(EXIT_SUCCESS);
		if (!data->path)
		{
			printf("ebash: %s: No such file or directory\n", input->cmd[0]);
			exit(EXIT_SUCCESS);
		}
		data->join_path = x_path(data, input->cmd[0]);
		execve(data->join_path, input->cmd, data->env);
	}
	exit(EXIT_SUCCESS);
}

void	conditions(t_parse *input, t_data *data)
{
	if (input)
	{
		if (check_pipe(input))
		{
			input->operator++;
			ft_pipe(struct_to2arr(input), data->env, input, data);
		}
		else if (check_builtin_with_redirect(input, data) == 1)
		{
		}
		else if (fork() == 0)
			child(input, data);
		while (wait(NULL) != -1)
			;
	}
}

void	init(t_data *data)
{
	char	*str;
	t_parse	*input;

	sig_event_loop();
	while (1)
	{
		str = readline(MINISHELL);
		if (!str)
		{
			printf("\033[1A\033[6Cexit\n");
			exit(EXIT_SUCCESS);
		}
		input = parsing(str, data->env_lst);
		data->env = join_key_and_val(data->env_lst);
		data->path = find_path(data->env);
		conditions(input, data);
		unlink("heredoc");
		data->join_path = NULL;
		if (*str)
			add_history(str);
		free(str);
	}
}
