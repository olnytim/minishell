/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:56 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/19 20:30:13 by timelkon         ###   ########.fr       */
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

// void write_quotes(char *line, char *new, int *i, int *j)
// {
// 	char q;

// 	q = line[*i];
// 	// new[*j] = line[*i];
// 	while (line[*i] == 34 || line[*i] == 39)
// 		*i += 1;
// 	// *j += 1;
// 	while (line[*i] != q)
// 	{
// 		new[*j] = line[*i];
// 		*i += 1;
// 		*j += 1;
// 	}
// 	if (line[*i + 1] == 34 || line[*i + 1] == 39)
// 		write_quotes(line, new, i, j);
// 	else
// 		*j -= 1;
// 	// *i += 1;
// 	return ;
// }

// char *epur_str(char *line, int j)
// {
// 	int i;
// 	int flag;
// 	char *new;

// 	new = malloc(ft_strlen(line) * (char)+1);
// 	i = 0;
// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	while (line[i])
// 	{
// 		if ((line[i] == ' ' || line[i] == '\t'))
// 			flag = 1;
// 		if (line[i] != ' ' && line[i] != '\t')
// 		{
// 			if (flag == 1)
// 				new[j++] = '_';
// 			flag = 0;
// 			if (line[i] == 34 || line[i] == 39)
// 				write_quotes(line, new, &i, &j);
// 			if (line[i] != 34 && line[i] != 39 && line[i] != ' ')
// 				new[j] = line[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

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

int	operator_after_pipe(char *line, int i)
{
	char	q;

	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q)
				i++;
		}
		if (line[i] == '|')
		{
			while ((line[i] == ' ' || line[i] == '\t') && line[i])
				i++;
			if (line[i] == '\0' || line[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	operators_in_a_row(char *line, int i)
{
	char	q;
	char	c;

	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q)
				i++;
		}
		if (line[i] == '>' || line[i] == '<')
		{
			c = line[i];
			if (line[i + 1] == c)
				i++;
			i++;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			if (line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

// char	*desipher_dollar(char *line, int i, int j)
// {
// 	char	*buf;
// 	char	*str;

// 	buf = malloc(ft_strlen(line) + 1);
// 	while (line[i])
// 	{
		
// 	}
// }

t_parse *parsing(char *line)
{
	int		i;
	t_parse	*splited;
	// char	*true_line;

	i = 0;
	if (!check_quotes(line))
		return (error(0));
	if (!operator_after_pipe(line, 0))
		return (error(1));
	if (!operators_in_a_row(line, 0))
		return (error(2));
	// true_line = desipher_dollar(line, 0, 0);
	printf("%s\n", line);
	splited = smart_split(line);
	int a = 1;
	while (splited)
	{
		printf("\nnode #%i\n", a);
		i = 0;
		printf("cmd ==\n");
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
