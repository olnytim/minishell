/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:33:57 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/09 16:40:13 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_struct(char *line, int i, int w)
{
	while (line[i])
	{
		if (line[i] == '|')
			w++;
		i++;
	}
	return (w);
}

t_parse	*devider(char *line, t_parse *split, int i, int j)
{
	int		start;
	t_parse	*temp;
	int		count;

	count = count_struct(line, 0, 0) + 1;
	while (--count)
	{
		temp = malloc(sizeof(t_parse));
		if (!temp)
			return (NULL);
		temp->next = NULL;
		temp->prev = NULL;
		args_split(line, temp, 0, 0);
		ft_lstadd_back_shell(&split, temp);
	}
}

t_parse	smart_split(char *line)
{
	t_parse	split;

	if (!line)
		return ;
	devider(line, &split, 0, 0);
}
