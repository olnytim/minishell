/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:18:31 by vfedorov          #+#    #+#             */
/*   Updated: 2023/10/23 19:05:01 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_parse *input)
{
	int	i;

	i = 0;
	if (input->cmd[1] && *input->cmd[1] && input->cmd[2] && *input->cmd[2])
		return (g_exit_code = 1, printf("5051: exit: too many arguments\n"));
	else if (input->cmd[1])
	{
		printf("exit\n");
		if (!ft_isdigit(input->cmd[1][i]))
		{
			printf("5051: exit: %s: numeric argument required\n",
				input->cmd[1]);
			exit(255);
		}
		while (input->cmd[1][i++])
		{
			if (input->cmd[1][i] == '+' || input->cmd[1][i] == '-')
				i++;
		}
	}
	if (input->cmd[1])
		exit(ft_atoi(input->cmd[1]));
	exit(0);
}
