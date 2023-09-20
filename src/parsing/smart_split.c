/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:38:59 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:25:06 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_struct(char *line, int i, int w)
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

t_parse	*devider(char *line)
{
	t_parse	*split;
	t_parse	*temp;
	int		count;
	int		i;

	i = 0;
	split = NULL;
	count = count_struct(line, 0, 0) + 1;
	while (count)
	{
		temp = malloc(sizeof(t_parse));
		if (!temp)
			return (NULL);
		temp->t_tig = ft_calloc(1, sizeof(t_tig));
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

t_parse	*smart_split(char *line)
{
	t_parse	*res;

	if (!line)
		return (NULL);
	res = devider(line);
	return (res);
}
