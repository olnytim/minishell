/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:40:37 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/07 20:24:29 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_size(t_parse *lst)
{
	size_t	counter;

	counter = 0;
	while (lst)
	{
		lst = lst->next;
		++counter;
	}
	return (counter);
}

char	**struct_to2arr(t_parse *lst)
{
	char	**arr;
	size_t	size;
	size_t	i;

	size = ft_parse_size(lst);
	arr = malloc(sizeof(char *) * (size + 1) + 3);
	if (!arr)
		return (NULL);
	i = 0;
	arr[i++] = ft_strdup("minishell");
	arr[i++] = ft_strdup("/dev/stdin");
	while (lst)
	{
		arr[i] = ft_strdup(lst->cmd);
		lst = lst->next;
		++i;
	}
	arr[i++] = ft_strdup("/dev/stdout");
	arr[i] = NULL;
	return (arr);
}

void	init(t_data *data)
{
	char	**args;
	char	*str;
	// t_parse	ls;
	// t_parse	wc;
	t_parse	echo;

	data->path = find_path(data->env);
	while (1)
	{
		// ls.cmd = "ls -l";
		// ls.operator = "|";
		// ls.next = &wc;
		// wc.cmd = "wc";
		// wc.next = NULL;
		// ls.operator = NULL;
		// int size = ft_parse_size(&ls);
		// char **argv = struct_to2arr(&ls);
		// ft_pipe(size + 3, argv, data->env);
		// exit(0);

		echo.cmd = "wc";
		echo.operator = "<<";
		echo.lim = "lim";
		echo.file = "file1";
		echo.next = NULL;
		
		str = readline(MINISHELL);
		if (!str)
			exit(EXIT_SUCCESS);
		args = ft_split(echo.cmd, ' ');
		if (*str)
		{
			if (fork() == 0)
			{
				ft_redirect(&echo);
				if (check_builtin(&echo) == 1)
					exit(EXIT_SUCCESS);
				else
				{
					data->join_path = x_path(data, args[0]);
					execve(data->join_path, args, data->env);
				}
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
