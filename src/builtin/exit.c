/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:35:02 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/08/28 12:24:40 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exit(t_parse *input)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (*input->cmd[2])
	{
		printf("ebash: exit: too many arguments\n");
		return ;
	}
	if (input->cmd[1])
	{
		while (input->cmd[1][i])
		{
			if (!ft_isdigit(input->cmd[1][i++]))
			{
				printf("ebash: exit: %s: numeric argument required\n",
				input->cmd[1]);
				exit(255);
			}
		}
	}
	exit(0);
}