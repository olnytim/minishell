/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:41:14 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/02 16:58:19 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lower_input(char *line)
{
	int i;
	
	i = 0;
	while (line[i] != '\0')
	{
		line[i] = (char)ft_tolower(line[i]);
		i++;
	}
}

int	parsing(char *line)
{
	int	i;

	i = 0;
	lower_input(line);
	printf("%s\n", line);
	return 0;
}
