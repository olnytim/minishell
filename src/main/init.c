/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/22 01:50:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*duble_pointers(t_parse *input)
{
	t_parse	*temp;
	t_parse	*t_input;
	t_parse	*head;
	int		size;

	t_input = input;
	size = ft_lstsize_t_parse(input);
	temp = NULL;
	head = NULL;
	if (!input)
		return (NULL);
	while (size--)
	{
		temp = malloc(sizeof (t_parse));
		temp->cmd = t_input->cmd;
		temp->operator = t_input->operator;
		temp->file = t_input->file;
		temp->lim = t_input->lim;
		temp->t_tig = t_input->t_tig;
		temp->next = NULL;
		temp->prev = NULL;
		ft_lstadd_back_shell(&head, temp);
		t_input = t_input->next;
	}
	return (head);
}

void	child(t_parse *input, t_data *data)
{
	int		status;
	pid_t	child;

	status = ft_redirect(input);
	if (status == -1)
		return ;
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigline);
	child = fork();
	if (child == 0)
	{
		if (!*input->cmd)
			exit(EXIT_FAILURE);
		if (!data->path && input->cmd[0][0] != '/')
			exit_message_for_ebash(input->cmd[0]);
		ft_redirect_dup(input, status);
		data->join_path = x_path(data, input->cmd[0]);
		if (!data->join_path)
			execve(input->cmd[0], input->cmd, data->env);
		execve(data->join_path, input->cmd, data->env);
	}
	wait(&status);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
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

int	init_empty_free(char *str, t_parse *input)
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
	g_exit_code = 0;
	return (1);
}

void	init(t_data *data)
{
	char	*str;
	t_parse	*input;

	while (1)
	{
		sig_event_loop();
		str = readline(MINISHELL);
		sig_ex(str);
		if (str[0] == '$' && str[1] == '\0')
		{
			add_history(str);
			free(str);
			printf(NO_CMD, "$");
			g_exit_code = 127;
			continue ;
		}
		input = parsing(str, data->env_lst);
		if (input && !*input->cmd && !*input->file && !*input->lim)
		{
			if (str && init_empty_free(str, input))
				continue ;
		}
		init_cont_1(data, input, str);
	}
}
