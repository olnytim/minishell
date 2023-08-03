/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:41:14 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/03 20:57:05 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	epur_str(char *line)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
	
// }

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	if (!ft_strchr(line, 34) || !ft_strchr(line, 39))
		return (0);
	while (line[i] != 34)
		i++;
	i++;
	while (line[i] != 34)
	return (1);
}

// void	lower_input(char *line)
// {
// 	int i;
	
// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		line[i] = (char)ft_tolower(line[i]);
// 		i++;
// 	}
// }

int	parsing(char *line)
{
	int	i;

	i = 0;
	// lower_input(line);
	if (!check_quotes(line))
		error_parsing();
	// epur_str(line);
	// printf("%s\n", line);
	return 0;
}
