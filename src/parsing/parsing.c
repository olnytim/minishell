/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:56 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/31 12:48:38 by mac              ###   ########.fr       */
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
			i++;
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
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q)
				i++;
		}
		i++;
	}
	return (1);
}

t_parse *parsing(char *line, t_env *env)
{
	t_parse	*splited;
	char	*true_line;

	// printf("line == %s\n\n", line);
	if (!check_quotes(line))
		return (error(0));
	if (!operator_after_pipe(line, 0))
		return (error(1));
	if (!operators_in_a_row(line, 0))
		return (error(2));
	if (ft_strchr(line, 36))
		true_line = desipher_dollar(line, env, 0, 0);
	else
	{
		true_line = ft_strdup(line);
		// free(line);
	}
	printf("%s\n", line);
	// int i = 0;
	splited = smart_split(true_line);
	// t_parse *temp = splited;
	// int a = 1;
	// while (temp)
	// {
	// 	printf("\nnode #%i\n", a);
	// 	i = 0;
	// 	printf("cmd ==\n");
	// 	while (splited->cmd[i])
	// 		printf("%s\n", splited->cmd[i++]);
	// 	i = 0;
	// 	printf("\noperator ==\n");
	// 	while (splited->operator[i])
	// 		printf("%s\n", splited->operator[i++]);
	// 	i = 0;
	// 	printf("\nfile ==\n");
	// 	while (splited->file[i])
	// 		printf("%s\n", splited->file[i++]);
	// 	i = 0;
	// 	printf("\nlimiter ==\n");
	// 	while (splited->lim[i])
	// 		printf("%s\n", splited->lim[i++]);
	// 	printf("\n-------\n");
	// 	temp = temp->next;
	// 	a++;
	// }
	// exit (0);
	return (splited);
}
