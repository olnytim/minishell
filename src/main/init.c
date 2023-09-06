/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/04 15:35:52 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*duble_pointers(t_parse *input)
{
	t_parse	*temp;

	if (!input)
		return (NULL);
	temp = malloc(sizeof (t_parse));
	temp->cmd = input->cmd;
	temp->operator = input->operator;
	temp->file = input->file;
	temp->lim = input->lim;
	temp->next = input->next;
	temp->prev = input->prev;
	
	return (temp);
}

void	child(t_parse *input, t_data *data)
{
	int	status;

	status = ft_redirect(input);
	if (status == -1)
		return ;
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
	t_parse	*input_free;

	while (1)
	{
		sig_event_loop();
		str = readline(MINISHELL);
		// str = ft_strdup("ls | wc -l >> a");
		if (!str)
		{
			printf("\n\033[1A\033[6Cexit\n");
			exit(EXIT_SUCCESS);
		}
		input = parsing(str, data->env_lst);
		if (input && !*input->cmd && !*input->file)
		{
			if (*str)
				add_history(str);
			free(str);
			free(input->cmd);
			free(input->file);
			free(input->lim);
			free(input->operator);
			free(input->t_tig);
			free(input);
			system("leaks minishell");
			continue ;
		}
		// exit (0);
		data->env = join_key_and_val(data->env_lst);
		data->path = find_path(data->env);
		input_free = duble_pointers(input);
		conditions(input, data);
		unlink("heredoc");
		data->join_path = NULL;
		if (*str)
			add_history(str);
		free2d(data->env);
		free_input(input_free, input);
		free(str);
		system("leaks minishell");
		// exit (0);
	}
}
