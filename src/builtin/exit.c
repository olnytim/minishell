/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:35:02 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/16 16:12:05 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_parse *input)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (input->cmd[2] && *input->cmd[2])
		return (printf("ebash: exit: too many arguments\n"));
	else if (input->cmd[1])
	{
		if (!ft_isdigit(input->cmd[1][i]))
		{
			printf("ebash: exit: %s: numeric argument required\n",
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
