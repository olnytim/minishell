/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:44:53 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/09 17:53:45 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd(int i, int w, char *line, t_parse *split)
{
	while (line[i] || line[i] != '|')
	{
		if (line[i] != '_' && line[i] != '>' && (line[i] != '>' &&
			line[i + 1] != '>') && line[i] != '<' &&
				(line[i] != '<' && line[i + 1] != '<'))
			w++;
		while ((line[i] != '_' && line[i]) || line[i] != '|')
		{
			if (line[i] == '|')
				return ;
			i++;
		}
		else
			while (line[i] == '_')
				i++;
	}
}

void	*args_split(char *line, t_parse *split, int i, int e)
{
	int start;

	split->cmd = malloc(count_cmd(0, 0, line, split) * sizeof(char *));
	split->file = malloc(count_file(0, 0, line, split) * sizeof(char *));
	split->lim = malloc(count_lim(0, 0, line, split) * sizeof(char *));
	split->operator = malloc(count_oper(0, 0, line, split) * sizeof(char *));
	while (line[i])
	{
		while (line[i] == '_')
			i++;
		if (line[i] != '_' && line[i] != '>' && line[i] != '<' && 
			line[i] != '|' && line[i])
		{
			start = i;
			while (line[i] != '_' && line[i])
				i++;
			split->cmd[e] = ft_substr(line, start, (i - start));
		}
		else
			ops_file_lim_split(line, split, &i);
		e++;
	}
}
