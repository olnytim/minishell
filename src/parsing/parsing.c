/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:56 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:25:11 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line)
{
	int		i;
	char	q;

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
			while (line[i] && line[i] != q)
				i++;
		}
		if (line[i] == '|')
		{
			while ((line[++i] == ' ' || line[i] == '\t') && line[i])
				;
			if (line[i] == '\0' || line[i] == '|')
				return (0);
		}
		if (line[i])
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

	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			c = line[i];
			if (line[i + 1] == c)
				i++;
			i++;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			if (line[i] == '>' || line[i] == '<'
				|| line[i] == '|' || line[i] == '\0')
				return (0);
		}
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q)
				i++;
		}
	}
	return (1);
}

t_parse	*parsing(char *line, t_env *env)
{
	t_parse	*splited;
	char	*true_line;

	if (!check_quotes(line))
		return (error(0));
	if (!operator_after_pipe(line, 0))
		return (error(1));
	if (!operators_in_a_row(line, -1))
		return (error(2));
	if (ft_strchr(line, 36))
		true_line = desipher_dollar(line, env, 0, 0);
	else
		true_line = ft_strdup(line);
	splited = smart_split(true_line);
	free(true_line);
	true_line = NULL;
	return (splited);
}
