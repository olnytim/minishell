/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:13:24 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/21 20:10:00 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	desipher_dollar_1(char *line, int i)
{
	if (line[i] == '?' && line[i - 1] == '$')
		return (i + 1);
	while ((line[i] == '?' && line[i - 1] == '$')
		|| (line[i] && line[i] != '$' && line[i] != ' ' && line[i] != 92
			&& line[i] != '=' && line[i] != '@' && line[i] != '\t'
			&& line[i] != '?' && !(line[i] >= 33 && line[i] <= 47)))
		i++;
	return (i);
}

int	heredoc_skip(char *line, int i, t_dol *dol, int *j)
{
	while (line[i] == '<')
	{
		dol->buf[*j] = line[i++];
		*j += 1;
	}
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		dol->buf[*j] = line[i++];
		*j += 1;
	}
	dol->str = join_dol(dol->str, dol->buf, *j);
	*j = 0;
	return (i);
}
