/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:03 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/12 15:18:24 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_proc_buf(char *buf)
{
	char	*temp;

	temp = buf;
	if (!g_exit_code)
		buf = ft_itoa(0);
	else
		buf = ft_itoa(g_exit_code);
	free(temp);
	return(buf);
}

char	*fill_dol_buf(char *buf, char *val, int i, int j)
{
	while (val[i])
	{
		if (val[i] == '>' || val[i] == '<' || val[i] == '|')
		{
			buf[j++] = 39;
			while (val[i] == '>' || val[i] == '<' || val[i] == '|')
				i++;
			buf[j++] = 39;
		}
		buf[j++] = val[i++];
	}
	buf[j] = '\0';
	return (buf);
}

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
		return(free(str), free(buf), temp);
	}
	return (str);
}

char	*check_dollar(char *line, t_env *env, char *str, int flag)
{
	t_env	*temp;
	char	*dol;
	int		i;

	i = 1;
	temp = env;
	while (line[i] && line[i] != '$' && line[i] != ' ' &&
		line[i] != '=' && line[i] != '@' && line[i] != '\t' &&
			line[i] != '?' && !(line[i] >= 33 && line[i] <= 47))
		i++;
	if (line[i] == '?' && line[i - 1] == '$')
	{
		dol = ft_strdup("?");
		str = write_dollar("$", str, dol, flag);
		return (free(dol), str);
	}
	dol = ft_substr(line, 1, i - 1);
	while (temp && temp->key)
	{
		if (ft_strncmp(dol, temp->key, ft_strlen(dol)) == 0 &&
			ft_strncmp(dol, temp->key, ft_strlen(temp->key)) == 0)
		{
			str = write_dollar(temp->val, str, dol, flag);
			return (free(dol), str);
		}
		temp = temp->next;
	}
	if (!*dol && line[i] != '$' && line[i - 2] != '$')
		str = write_dollar("$", str, dol, flag);
	return (free(dol), str);
}

char	desipher_dollar_cont_1(char *line, char q, int *flag, int *i)
{
	if (flag && line[*i] == q)
	{
		q = 0;
		flag = 0;
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
			while ((line[i] == '?' && line[i - 1] == '$') || (line[i] && line[i] != '$' && line[i] != ' ' &&
				line[i] != '=' && line[i] != '@' && line[i] != '\t' &&
					line[i] != '?' && !(line[i] >= 33 && line[i] <= 47)))
				i++;
		}
		while (line[i] && line[i] != '$')
		{
			if (line[i] == 34 || line[i] == 39)
				dol.q = desipher_dollar_cont_1(line, dol.q, &dol.flag, &i);
			dol.buf[j++] = line[i++];
		}
		dol.str = join_dol(dol.str, dol.buf, j);
		j = 0;
	}
	return (free(dol.buf), dol.str);
}
