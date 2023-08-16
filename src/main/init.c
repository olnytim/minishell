/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/16 19:07:27 by vfedorov         ###   ########.fr       */
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
		cmd1.operator = "";
		cmd1.lim = "";
		cmd1.file = "";
		cmd1.next = NULL;
		
		str = "cat";
		cmd2.cmd = ft_split(str, ' ');
		cmd2.operator = ">";
		cmd2.file = "file1";	
		cmd2.next = NULL;

		str = readline(MINISHELL); 
		if (!str)
			exit(EXIT_SUCCESS);
		cmd1.cmd = ft_split(str, ' ');
		data->env = join_key_and_val(data->env_lst);
		data->path = find_path(data->env);
		if (*str)
		{
			if (check_builtin(&cmd1, data) == 1)
			{
				
			}
			else if (fork() == 0)
			{
				// ft_pipe(ft_parse_size(&cmd1) + 3, struct_to2arr(&cmd1), data->env);
				// ft_redirect(&cmd2);
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
