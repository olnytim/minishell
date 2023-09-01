/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:15:25 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/01 15:13:55 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
}

void	echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}

void	print2d(char **arr)
{
	int	i;
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	env(t_data *data)
{
	print2d(data->env);
}
