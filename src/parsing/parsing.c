/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:56 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/12 19:46:21 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void lower_input(char *line)
// {
//  int i;

//  i = 0;
//  while (line[i] != '\0')
//  {
//   line[i] = (char)ft_tolower(line[i]);
//   i++;
//  }
// }

void write_quotes(char *line, char *new, int *i, int *j)
{
	char q;

	q = line[*i];
	// new[*j] = line[*i];
	while (line[*i] == 34 || line[*i] == 39)
		*i += 1;
	// *j += 1;
	while (line[*i] != q)
	{
		new[*j] = line[*i];
		*i += 1;
		*j += 1;
	}
	if (line[*i + 1] == 34 || line[*i + 1] == 39)
		write_quotes(line, new, i, j);
	else
		*j -= 1;
	// *i += 1;
	return ;
}

char *epur_str(char *line, int j, int **op_ocur)
{
	int i;
	int flag;
	char *new;

	new = malloc(ft_strlen(line) * (char)+1);
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
				new[j++] = '_';
			flag = 0;
			if (line[i] == 34 || line[i] == 39)
				write_quotes(line, new, &i, &j);
			if (line[i] != 34 && line[i] != 39 && line[i] != ' ')
				new[j] = line[i];
			j++;
		}
		i++;
	}
	new[i] = '\0';
	return (new);
}

int check_quotes(char *line)
{
	int i;
	char q;

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

t_parse *parsing(char *line)
{
	int		i;
	char	*spaced_line;
	t_parse	*splited;
	int		*op_ocur;

	i = 0;
	// lower_input(line);
	if (!check_quotes(line))
	{
		write(2, "Error: please close the brackets\n", 33);
		return (0);
	}
	spaced_line = epur_str(line, 0, &op_ocur);
	printf("%s\n", spaced_line);
	splited = smart_split(spaced_line);
	int a = 1;
	while (splited)
	{
		printf("\nnode #%i\n", a);
		i = 0;
		printf("cmd ==\n\n");
		while (splited->cmd[i])
			printf("%s\n", splited->cmd[i++]);
		i = 0;
		printf("\noperator ==\n");
		while (splited->operator[i])
			printf("%s\n", splited->operator[i++]);
		i = 0;
		printf("\nfile ==\n");
		while (splited->file[i])
			printf("%s\n", splited->file[i++]);
		i = 0;
		printf("\nlimiter ==\n");
		while (splited->lim[i])
			printf("%s\n", splited->lim[i++]);
		printf("\n-------\n");
		splited = splited->next;
		a++;
	}
	return (splited);
}
