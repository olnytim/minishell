/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:37:50 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/16 19:45:48 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_file(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			w++;
			if (line[i] == '>' && line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (w);
}

int count_lim(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			w++;
			i++;
		}
		i++;
	}
	return (w);
}

int count_oper(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
				i++;
			w++;
		}
		i++;
	}
	return (w);
}

int count_cmd(int i, int w, char *line)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] != '_' && line[i] != '>' && (line[i] != '>' && line[i + 1] != '>') && line[i] != '<' && (line[i] != '<' && line[i + 1] != '<') && line[i] != '|' && line[i])
			w++;
		while ((line[i] != '_' || line[i] != '>' || line[i] != '<' || line[i] != '|') && (line[i]))
			i++;
		i++;
	}
	return (w);
}

void ops_file_lim_split(char *line, t_parse *split, int *i)
{
	int start;
	char c;

	if (line[*i] == '>' || line[*i] == '<')
	{
		c = line[*i];
		start = *i;
		if (line[*i + 1] == c)
			*i += 1;
		split->operator[split->t_tig->i_op] = ft_substr(line, start, (*i - start + 1));
		*i += 1;
		while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
			*i += 1;
		start = *i;
		while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '>'
			&& line[*i] != '<' && line[*i] != '|' && line[*i])
			*i += 1;
		if (ft_strncmp(split->operator[split->t_tig->i_op++], "<<", 2) == 0)
			split->lim[split->t_tig->i_lm++] = ft_substr(line, start, (*i - start));
		else
			split->file[split->t_tig->i_fl++] = ft_substr(line, start, (*i - start));
	}
	// else if (line[*i] == '|')
		// split->operator[split->t_tig->i_op++] = ft_strdup("|");
}

int	count_buf(int i, int w, char *line)
{
	char	q;

	while (line[i] && line[i] != '|')
	{
		if (line[i] == 34 || line[i] == 39)
			q = line[i++];
		if (line[i] == q)
			i++;
		i++;
		w++;
	}
	return (w);
}

void	quote_handle(char *line, char *buf, int *i, int *j)
{
	char	q;

	q = line[*i];
	*i += 1;
	while (line[*i] != q)
	{
		buf[*j] = line[*i];
		*j += 1;
		*i += 1;
	}
	*i += 1;
}

int args_split(char *line, t_parse *split, int i, int j)
{
	// int 	start;
	char	*buf;
	// int		flag;
	// char	q;

	split->cmd = malloc((count_cmd(0, 0, line) + 1) * sizeof(char *));
	split->file = malloc((count_file(0, 0, line) + 1) * sizeof(char *));
	split->lim = malloc((count_lim(0, 0, line) + 1) * sizeof(char *));
	split->operator = malloc((count_oper(0, 0, line) + 1) * sizeof(char *));
	buf = malloc((count_buf(0, 0, line) + 1) * sizeof(char));
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '>' &&
			line[i] != '<' && line[i] != '|' && line[i])
		{
			while (line[i] != ' ' && line[i] != '\t' && line[i] != '>' &&
				line[i] != '<' && line[i] != '|' && line[i])
			{
				if (line[i] == 34 || line[i] == 39)
					quote_handle(line, buf, &i, &j);
				buf[j++] = line[i++];
			}
			split->cmd[split->t_tig->i_cmd++] = ft_strdup(buf);
			buf = &buf[j];
			j = 0;
		}
		else
			ops_file_lim_split(line, split, &i);
	}
	buf[j] = '\0';
	if (line[i] == '|')
	{
		split->operator[split->t_tig->i_op++] = ft_strdup("|");
		i++;
	}
	// split->cmd[split->t_tig->i_cmd++] = ft_strdup(buf);
	// free (buf);
	split->operator[split->t_tig->i_op] = NULL;
	split->file[split->t_tig->i_fl] = NULL;
	split->lim[split->t_tig->i_lm] = NULL;
	split->cmd[split->t_tig->i_cmd] = NULL;
	return (i);
}
