/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/11 17:54:09 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(t_data *data)
{
	char	**args;
	char	*str;
	t_parse	cmd1;
	t_parse	cmd2;

	data->path = find_path(data->env);
	while (1)
	{
		str = "> >";
		cmd1.operator = ft_split(str, ' ');
		// cmd1.lim[0] = "";
		str = "file1 file2";
		cmd1.file = ft_split(str, ' ');
		// cmd1.next = &cmd2;
		cmd1.next = NULL;

		str = "env";
		cmd2.cmd = ft_split(str, ' ');
		str = ">";
		cmd2.operator = ft_split(str, ' ');
		str = "file1";
		cmd2.file = ft_split(str, ' ');
		cmd2.next = NULL;

		str = readline(MINISHELL);
		if (!str)
			exit(EXIT_SUCCESS);
		cmd1.cmd = ft_split(str, ' ');
		if (*str)
		{
			if (cmd1.operator[0][0] == '|')
				ft_pipe(struct_to2arr(&cmd1), data->env, &cmd1, data);
			else if (check_builtin_with_redirect(&cmd1, data) == 1)
			{
				if (check_builtin(args) == 1)
				{
				}
				else if (fork() == 0)
				{
					data->join_path = x_path(data, args[0]);
					execve(data->join_path, args, data->env);
				}
				while (wait(NULL) != -1)
					;
				data->join_path = NULL;
				args = NULL;
				add_history(str);
				free(str);
			}
			else if (fork() == 0)
			{			
				ft_redirect(&cmd1);
				data->join_path = x_path(data, cmd1.cmd[0]);
				execve(data->join_path, cmd1.cmd, data->env);
			}
			while (wait(NULL) != -1)
				;
			unlink("heredoc");
			data->join_path = NULL;
			args = NULL;
			add_history(str);
			free(str);
		}
	}
}
