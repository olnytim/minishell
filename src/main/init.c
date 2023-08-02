/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/02 15:57:04 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(char **envp, t_data *data)
{
	char	**args;
	char	*str;

	data->path = find_path(envp);
	while (1)
	{
		str = readline(MINISHELL);
		if (!str)
			exit(EXIT_SUCCESS);
		args = ft_split(str, ' ');
		if (*str)
		{
			if (check_builtin(args) == 1)
			{
			}
			else if (fork() == 0)
			{
				data->join_path = x_path(data, args[0]);
				execve(data->join_path, args, envp);
			}
			while (wait(NULL) != -1)
				;
			data->join_path = NULL;
			args = NULL;
			add_history(str);
			free(str);
		}
	}
}
