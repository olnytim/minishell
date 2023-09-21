/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:03 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/21 20:09:36 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*write_dollar(char *val, char *str, char *dol, int flag)
{
	char	*temp;
	char	*buf;

	if (flag == 2)
	{
		temp = ft_strjoin_nl(str, "$");
		free(str);
		str = ft_strjoin_nl(temp, dol);
		free(temp);
	}
	else
	{
		buf = malloc(count_wr_dol_buf(val) + 1);
		if (ft_strlen(dol) == 1 && *dol == '?')
			buf = fill_proc_buf(buf);
		else
			buf = fill_dol_buf(buf, val, 0, 0);
		if (!str)
			temp = ft_strdup(buf);
		else
			temp = ft_strjoin_nl(str, buf);
		return (free(str), free(buf), temp);
	}
	return (str);
}

int	check_dollar_1(char *line, int i)
{
	while (line[i] && line[i] != '$' && line[i] != ' '
		&& line[i] != '=' && line[i] != '@' && line[i] != '\t'
		&& line[i] != 92 && line[i] != '?'
		&& !(line[i] >= 33 && line[i] <= 47))
		i++;
	return (i);
}

char	*check_dollar_2(char *dol, char *str, int flag)
{
	dol = ft_strdup("?");
	str = write_dollar("$", str, dol, flag);
	return (free(dol), str);
}

char	*check_dollar(char *line, t_env *env, char *str, int flag)
{
	t_env	*temp;
	char	*dol;
	int		i;

	dol = NULL;
	i = 1;
	temp = env;
	i = check_dollar_1(line, i);
	if (line[i] == '?' && line[i - 1] == '$')
		return (check_dollar_2(dol, str, flag));
	dol = ft_substr(line, 1, i - 1);
	while (temp && temp->key)
	{
		if (ft_strncmp(dol, temp->key, ft_strlen(dol)) == 0
			&& ft_strncmp(dol, temp->key, ft_strlen(temp->key)) == 0)
		{
			str = write_dollar(temp->val, str, dol, flag);
			return (free(dol), str);
		}
		temp = temp->next;
	}
	if (!*dol && line[i] != '$')
		str = write_dollar("$", str, dol, flag);
	return (free(dol), str);
}

char	*desipher_dollar(char *line, t_env *env, int i, int j)
{
	t_dol	dol;

	dol.flag = 0;
	dol.str = NULL;
	dol.buf = malloc(ft_strlen(line) + 1);
	while (line[i])
	{
		if (line[i] && line[i] == '$')
		{
			dol.str = check_dollar(&line[i], env, dol.str, dol.flag);
			i++;
			i = desipher_dollar_1(line, i);
		}
		while (line[i] && line[i] != '$')
		{
			if (line[i] == '<' && line[i + 1] == '<')
				i = heredoc_skip(line, i, &dol, &j);
			if (line[i] == 34 || line[i] == 39)
				dol.q = desipher_dollar_cont_1(line, dol.q, &dol.flag, &i);
			dol.buf[j++] = line[i++];
		}
		dol.str = join_dol(dol.str, dol.buf, j);
		j = 0;
	}
	return (free(dol.buf), dol.str);
}
