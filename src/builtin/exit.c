/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:35:02 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/04 13:17:28 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_parse *input)
{
	int	i;

	i = 0;
	if (input->cmd[2] && *input->cmd[2])
	{
		printf("ebash: exit: too many arguments\n");
		return ;
	}
	else if (input->cmd[1])
	{
		printf("exit\n");
		while (input->cmd[1][i])
		{
			if (input->cmd[1][i] == '+' || input->cmd[1][i] == '-')
				i++;
			if (!ft_isdigit(input->cmd[1][i++]))
			{
				printf("ebash: exit: %s: numeric argument required\n",
					input->cmd[1]);
				exit(255);
			}
		}
	}
	if (input->cmd[1])
		exit(ft_atoi(input->cmd[1]));
	exit(0);
}
