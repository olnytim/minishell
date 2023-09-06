/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:56 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/02 17:00:12 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_quotes(char *line)
{
	int i;
	char q;

	i = 0;
	if (!ft_strchr(line, 34) && !ft_strchr(line, 39))
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
	char	*str;

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
	str = ft_strtrim(line, " ");
	if (*str == '|')
		return (free(str), 0);
	return (free(str), 1);
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
		true_line = ft_strdup(line);
	// printf("%s\n", line);
	// int i = 0;
	printf("%lu\n", sizeof (char **));
	printf("%lu\n", sizeof (int *));
	printf("%lu\n", sizeof (t_tig));
	printf("%lu\n", sizeof (t_parse));
	printf("%lu\n", sizeof (t_data));
	printf("%lu\n", sizeof (t_env));
	splited = smart_split(true_line);
	free(true_line);
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
