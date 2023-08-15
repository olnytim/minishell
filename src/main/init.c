/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/15 20:19:11 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(t_data *data)
{
	char	*str;
	t_parse	*input;

	sig_event_loop();
	while (1)
	{
		str = readline(MINISHELL);
		if (!str)
			exit(EXIT_SUCCESS);
		input = parsing(str);
		data->env = join_key_and_val(data->env_lst);
		data->path = find_path(data->env);
		if (input)
		{
			if (*input->operator && *input->operator[0] == '|')
			{
				input->operator++;
				ft_pipe(struct_to2arr(input), data->env, input, data);
			}
			else if (check_builtin_with_redirect(input, data) == 1)
			{
			}
			else if (fork() == 0)
			{
				if (!*input->cmd)
					exit(EXIT_SUCCESS);
				ft_redirect(input);
				if (!data->path)
				{
					printf("ebash: %s: No such file or directory\n", input->cmd[0]);
					exit(EXIT_SUCCESS);
				}
				data->join_path = x_path(data, input->cmd[0]);
				execve(data->join_path, input->cmd, data->env);
			}
			while (wait(NULL) != -1)
				;
			unlink("heredoc");
			data->join_path = NULL;
			add_history(str);
			free(str);
		}
	}
}
