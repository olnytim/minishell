/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:56:25 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/04 18:35:27 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_buf(int i, int w, char *line)
{
	char	q;
	int		flag;

	while (line[i] && line[i] != '|')
	{
		if (flag != 1 && (line[i] == 34 || line[i] == 39))
		{
			flag = 1;
			q = line[i++];
		}
		if (line[i] == q && flag)
		{
			flag = 0;
			i++;
		}
		if (line[i])
		{
			w++;
			i++;
		}
	}
	return (w);
}

int count_cmd(int i, int w, char *line)
{
	char	q;

	while (line[i] && line[i] != '|')
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t' ||
			line[i] == '>' || line[i] == '<'))
			i++;
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q)
				i++;
			i++;
		}
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '>'
			&& line[i] != '<')
			i++;
		w++;
	}
	return (w);
}

int count_file(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			w++;
			if (line[i] == '>' && line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (w);
}

int count_oper(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if ((line[i] == '>' && line[i + 1] == '>') ||
				(line[i] == '<' && line[i + 1] == '<'))
				i++;
			w++;
		}
		i++;
	}
	if (line[i] == '|')
		w++;
	return (w);
}

int count_lim(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			w++;
			i++;
		}
		i++;
	}
	return (w);
}
