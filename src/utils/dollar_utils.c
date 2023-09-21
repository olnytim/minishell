/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 22:56:44 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/21 19:28:33 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_dol(char *str, char *buf, int j)
{
	char	*temp;

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
		else
		{
			i++;
			w++;
		}
	}
	return (w);
}

char	*fill_proc_buf(char *buf)
{
	char	*temp;

	temp = buf;
	if (!g_exit_code)
		buf = ft_itoa(0);
	else
		buf = ft_itoa(g_exit_code);
	free(temp);
	return (buf);
}

char	*fill_dol_buf(char *buf, char *val, int i, int j)
{
	while (val[i])
	{
		if (val[i] == '>' || val[i] == '<' || val[i] == '|')
		{
			buf[j++] = 39;
			while (val[i] == '>' || val[i] == '<' || val[i] == '|')
				buf[j++] = val[i++];
			buf[j++] = 39;
		}
		if (val[i])
			buf[j++] = val[i++];
	}
	buf[j] = '\0';
	return (buf);
}

char	desipher_dollar_cont_1(char *line, char q, int *flag, int *i)
{
	if (flag && line[*i] == q)
	{
		q = 0;
		*flag = 0;
	}
	else if (line[*i] == 34 && *flag != 2)
	{
		q = line[*i];
		*flag = 1;
	}
	else if (*flag != 1)
	{
		q = line[*i];
		*flag = 2;
	}
	return (q);
}
