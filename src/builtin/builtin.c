/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:15:25 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/16 21:43:14 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
	g_exit_code = 0;
}

void	echo(char **args)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (ft_strncmp(args[i] + j, "n", ft_strlen(args[i] + j)) != 0)
			break ;
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	g_exit_code = 0;
}

void	env(t_data *data)
{
	print_linked_list(data->env_lst);
	g_exit_code = 0;
}
