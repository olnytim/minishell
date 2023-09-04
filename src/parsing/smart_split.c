/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:38:59 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/02 15:30:02 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_struct(char *line, int i, int w)
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
			w++;
		i++;
	}
	return (w);
}

t_parse *devider(char *line)
{
	t_parse	*split;
	t_parse *temp;
	int count;
	int	i;

	i = 0;
	split = NULL;
	count = count_struct(line, 0, 0) + 1;
	while (count)
	{
		temp = malloc(sizeof(t_parse));
		if (!temp)
			return (NULL);
		temp->t_tig = malloc(sizeof(t_tig));
		temp->t_tig->i_fl = 0;
		temp->t_tig->i_lm = 0;
		temp->t_tig->i_op = 0;
		temp->t_tig->i_cmd = 0;
		temp->fd_in = -1;
		temp->fd_out = -1;
		temp->next = NULL;
		temp->prev = NULL;
		i += args_split(&line[i], temp, 0, 0);
		ft_lstadd_back_shell(&split, temp);
		count--;
	}
	return (split);
}

t_parse *smart_split(char *line)
{
	// t_parse *split;
	t_parse	*res;

	// split = malloc(sizeof(t_parse));
	// split = NULL;
	if (!line)
		return (NULL);
	res = devider(line);
	return (res);
}
