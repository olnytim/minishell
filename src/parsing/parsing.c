/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:41:14 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/04 22:23:46 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"





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

void	write_quotes(char *line, char *new, int *i, int *j)
{
	char	q;

	q = line[*i];
	new[*j] = line[*i];
	*i += 1;
	*j += 1;
	while (line[*i] != q)
	{
		new[*j] = line[*i];
		*i += 1;
		*j += 1;
	}
	if (line[*i + 1] == 34 || line[*i + 1] == 39)
		write_quotes(line, new, i, j);
	return ;
}

char	*epur_str(char *line, int j)
{
	int		i;
	int		flag;
	char	*new;

	new = malloc (ft_strlen(line) * (char) + 1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t'))
			flag = 1;
		if (line[i] != ' ' && line[i] != '\t')
		{
			if (flag == 1)
				new[j++] = ' ';
			flag = 0;
			if (line[i] == 34 || line[i] == 39)
				write_quotes(line, new, &i, &j);
			new[j] = line[i];
			j++;
		}
		i++;
	}
	new[i] = '\0';
	// free(line);
	return (new);
}

int	check_quotes(char *line)
{
	int		i;
	char	q;

	i = 0;
	if (!strchr(line, 34) && !strchr(line, 39))
		return (1);
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q && line[i])
				i++;
			if (line[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

char	*parsing(char *line)
{
	int		i;
	char	*spaced_line;

	i = 0;
	// lower_input(line);
	if (!check_quotes(line))
	{
		write (2, "Error: please close the brackets\n", 33);
		return (0);
	}
	spaced_line = epur_str(line, 0);
	printf("%s\n", spaced_line);
	return (spaced_line);
}
