/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:03 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/24 16:58:19 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		desipher_double(char *line, t_env *env, int *i, int *j)
{
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[i] != )
	{
		
	}
}

char	*desipher_dollar(char *line, t_env *env, int i, int j)
{
	char	*buf;
	char	*str;
	int		flag;

	buf = malloc(ft_strlen(line) + 1);
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			if (line[i] == 34)
				flag = 1;
			else
				flag = 2;
			i++;
		}
		if (line[i] == '$' && flag != 2)
			flag = desipher_double(line, env, &i, &j);
		else if (line[i] == '$' && flag == 2)
			flag = desipher_single(line, &i, &j);
		else
			buf[j++] = line[i++];
	}
	str = ft_strdup(buf);
	return (str);
}
