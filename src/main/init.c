/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/14 21:33:31 by valeriafedo      ###   ########.fr       */
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
		if (!data->path)
		{
			printf("ebash: %s: No such file or directory\n", input->cmd[0]);
			exit(EXIT_FAILURE);
		}
		ft_redirect_dup(input, status);
		data->join_path = x_path(data, input->cmd[0]);
		execve(data->join_path, input->cmd, data->env);
	}
	waitpid(child, &status, 0);
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

void	init(t_data *data)
{
	char	*str;
	t_parse	*input;
	t_parse	*input_free;

	while (1)
	{
		sig_event_loop();
		str = readline(MINISHELL);
		if (!str)
		{
			printf("\n\033[1A\033[6Cexit\n");
			g_exit_code = 0;
			exit(EXIT_SUCCESS);
		}
		if (str[0] == '$' && str[1] == '\0')
		{
			add_history(str);
			free(str);
			printf(NO_CMD, "$");
			continue ;
		}
		input = parsing(str, data->env_lst);
		if (input && !*input->cmd && !*input->file && !*input->lim)
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
			g_exit_code = 127;
			continue ;
		}
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
	}
}
