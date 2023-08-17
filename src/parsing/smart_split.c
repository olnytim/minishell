/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:38:59 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/16 18:02:39 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_struct(char *line, int i, int w)
{
	while (line[i])
	{
		if (line[i] == '|')
			w++;
		i++;
	}
	return (w);
}

t_parse *devider(char *line, t_parse *split)
{
	t_parse *temp;
	int count;
	int	i;

	i = 0;
	split = malloc(sizeof(t_parse));
	count = count_struct(line, 0, 0) + 1;
	while (count)
	{
		temp = malloc(sizeof(t_parse));
		temp->t_tig = malloc(sizeof(t_tig));
		temp->t_tig->i_fl = 0;
		temp->t_tig->i_lm = 0;
		temp->t_tig->i_op = 0;
		temp->t_tig->i_cmd = 0;
		if (!temp)
			return (NULL);
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
	t_parse split;

	if (!line)
		return (NULL);
	return (devider(line, &split));
}
