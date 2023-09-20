/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:37:50 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:25:28 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ops_file_lim_split(char *line, t_parse *split, int *i)
{
	int		start;
	char	c;
	char	*str;

	if (line[*i] == '>' || line[*i] == '<')
	{
		c = line[*i];
		start = *i;
		if (line[*i + 1] == c)
			*i += 1;
		split->operator[split->t_tig->i_op]
			= ft_substr(line, start, (*i - start + 1));
		*i += 1;
		while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
			*i += 1;
		str = file_lim_quotes(line, i, 0);
		if (ft_strncmp(split->operator[split->t_tig->i_op++], "<<", 2) == 0)
			split->lim[split->t_tig->i_lm++] = ft_strdup(str);
		else
			split->file[split->t_tig->i_fl++] = ft_strdup(str);
		free (str);
	}
}

char	*args_split_cont_1(char *line, char *buf_ind, t_parse *split)
{
	split->cmd = malloc((count_cmd(0, 0, line) + 1) * sizeof(char *));
	split->file = malloc((count_file(0, 0, line) + 1) * sizeof(char *));
	split->lim = malloc((count_lim(0, 0, line) + 1) * sizeof(char *));
	split->operator = malloc((count_oper(0, 0, line) + 1) * sizeof(char *));
	buf_ind = malloc((count_buf(0, 0, line) + 1) * sizeof(char));
	buf_ind[count_buf(0, 0, line)] = '\0';
	return (buf_ind);
}

void	args_split_cont_2(char *line, char *buf_ind, t_parse *split, int *i)
{
	if (line[*i] == '|')
	{
		split->operator[split->t_tig->i_op++] = ft_strdup("|");
		*i += 1;
	}
	if (*split->operator)
		split->operator[split->t_tig->i_op] = NULL;
	if (*split->file)
		split->file[split->t_tig->i_fl] = NULL;
	if (*split->lim)
		split->lim[split->t_tig->i_lm] = NULL;
	if (*split->cmd)
		split->cmd[split->t_tig->i_cmd] = NULL;
	free(buf_ind);
	buf_ind = NULL;
}

int	args_split_cont_3(char *line, char *buf, t_parse *split, int *j)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '>' && line[i] != '<' && line[i] != '|')
	{
		if (line[i] == 34 || line[i] == 39)
			quote_handle(line, buf, &i, j);
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '>' && line[i] != '<' && line[i] != '|')
			buf[*j] = line[i];
		if (line[i] && line[i] != ' ' && line[i] != '\t')
		{
			i++;
			*j += 1;
		}
	}
	buf[*j] = '\0';
	split->cmd[split->t_tig->i_cmd++] = ft_strdup(buf);
	buf = &buf[*j];
	*j = 0;
	return (i);
}

int	args_split(char *line, t_parse *split, int i, int j)
{
	char	*buf;
	char	*buf_ind;

	buf_ind = NULL;
	buf_ind = args_split_cont_1(line, buf_ind, split);
	if (!split->cmd || !split->file || !split->lim
		|| !split->operator || !buf_ind)
		return (0);
	buf = buf_ind;
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '>'
			&& line[i] != '<' && line[i] != '|' && line[i])
			i += args_split_cont_3(&line[i], buf, split, &j);
		else
			ops_file_lim_split(line, split, &i);
	}
	return (args_split_cont_2(line, buf_ind, split, &i), i);
}
