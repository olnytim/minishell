/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:18:31 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:18:52 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_parse *input)
{
	int	i;

	i = 0;
	if (input->cmd[1] && *input->cmd[1] && input->cmd[2] && *input->cmd[2])
		return (printf("ebash: exit: too many arguments\n"));
	else if (input->cmd[1])
	{
		printf("exit\n");
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
