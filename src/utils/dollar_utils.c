/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 22:56:44 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/04 15:16:38 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_dol(char *str, char *buf, int j)
{
	char *temp;

	buf[j] = '\0';
	if (!str)
		temp = ft_strdup(buf);
	else
		temp = ft_strjoin_nl(str, buf);
	free(str);
	return (temp);
}

int	count_wr_dol_buf(char *val)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (val[i])
	{
		if (val[i] == '>' || val[i] == '<' || val[i] == '|')
		{
			while (val[i] == '>' || val[i] == '<' || val[i] == '|')
			{
				i++;
				w++;
			}
			w += 2;
		}
		i++;
		w++;
	}
	return (w);
}
