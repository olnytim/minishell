/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:03 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/28 20:03:45 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	write_dollar(char *buf, char *str, int *j)
{
	int		i;
	char	*val;

	i = 0;
	val = malloc(ft_strlen(val) + 1)
	while (val[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			buf[*j] = 39;
			while (str[i] == '>' || str[i] == '<' || str[i] == '|')
				i++;
			buf[*j] = 39;
		}
		buf[*j] = str[i++];
		*j += 1;
	}
	return (i);
}

int	check_dollar(char *line, char *buf, t_env *env, int *j)
{
	int		i;
	t_env	*temp;
	char	*dol;

	i = 1;
	temp = env;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && !(line[i] >= 33 && line[i] <= 47))
		i++; 
	dol = ft_substr(line, 1, i - 1);
	while (temp->key)
	{
		if (ft_strncmp(dol, temp->key, ft_strlen(dol)) == 0 &&
		ft_strncmp(dol, temp->key, ft_strlen(temp->key)) == 0)
		{
			write_dollar(buf, temp->val, j);
			free(dol);
			return (i);
		}
		temp = temp->next;
	}
	i = ft_strlen(dol) + 1;
	free(dol);
	return (i);
}

char	*desipher_dollar(char *line, t_env *env, int i, int j)
{
	char	*buf;
	char	*str;
	int		flag;
	char	q;

	buf = malloc(ft_strlen(line) + 1);
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			if (flag != 0 && line[i] == q)
				flag = 0;
			else if (line[i] == 34)
				flag = 1;
			else
				flag = 2;
			q = line[i];
			i++;
		}
		if (line[i] == '$' && flag != 2)
			i += check_dollar(&line[i], buf, env, &j);
		else
			buf[j++] = line[i++];
	}
	buf[j] = '\0';
	str = ft_strdup(buf);
	return (free(buf), str);
}
