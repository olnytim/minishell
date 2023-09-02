/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:03 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/30 21:58:36 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	write_dollar(char *buf, char *str, int *j)
// {
// 	int		i;
// 	char	*val;

// 	i = 0;
// 	val = malloc(ft_strlen(val) + 1)
// 	while (val[i])
// 	{
// 		while (str[i] == ' ' || str[i] == '\t')
// 		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
// 		{
// 			buf[*j] = 39;
// 			while (str[i] == '>' || str[i] == '<' || str[i] == '|')
// 				i++;
// 			buf[*j] = 39;
// 		}
// 		buf[*j] = str[i++];
// 		*j += 1;
// 	}
// 	return (i);
// }

// int	check_dollar(char *line, char *buf, t_env *env, char *str)
// {
// 	int		i;
// 	t_env	*temp;
// 	char	*dol;
// 	int		j;

// 	j = 0;
// 	i = 1;
// 	temp = env;
// 	while (line[i] && line[i] != ' ' && line[i] != '\t' && !(line[i] >= 33 && line[i] <= 47))
// 		i++; 
// 	dol = ft_substr(line, 1, i - 1);
// 	while (temp->key)
// 	{
// 		if (ft_strncmp(dol, temp->key, ft_strlen(dol)) == 0 &&
// 		ft_strncmp(dol, temp->key, ft_strlen(temp->key)) == 0)
// 		{
// 			write_dollar(buf, temp->val, j);
// 			free(dol);
// 			return (i);
// 		}
// 		temp = temp->next;
// 	}
// 	i = ft_strlen(dol) + 1;
// 	free(dol);
// 	return (i);
// }

char	*join_dol(char *str, char *buf, int j)
{
	char *temp;

	buf[j] = '\0';
	if (!str)
		temp = ft_strdup(buf);
	else
		temp = ft_strjoin_nl(str, buf);
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
		buf = fill_dol_buf(buf, val, 0, 0);
		if (!str)
			temp = ft_strdup(buf);
		else
			temp = ft_strjoin_nl(str, buf);
		free(str);
		free(buf);
		return(temp);
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
		line[i] != '\t' && !(line[i] >= 33 && line[i] <= 47))
		i++;
	dol = ft_substr(line, 1, i - 1);
	while (temp->key)
	{
		if (ft_strncmp(dol, temp->key, ft_strlen(dol)) == 0 &&
			ft_strncmp(dol, temp->key, ft_strlen(temp->key)) == 0)
		{
			str = write_dollar(temp->val, str, dol, flag);
			free(dol);
			return (str);
		}
		temp = temp->next;
	}
	free(dol);
	return (str);
}

char	*desipher_dollar(char *line, t_env *env, int i, int j)
{
	char	*buf;
	char	*str;
	int		flag;
	char	q;

	flag = 0;
	str = NULL;
	while (line[i])
	{
		buf = malloc(ft_strlen(line) + 1);
		if (line[i] && line[i] == '$')
		{
			str = check_dollar(&line[i], env, str, flag);
			i++;
			while (line[i] && line[i] != '$' && line[i] != ' ' &&
				line[i] != '\t' && !(line[i] >= 33 && line[i] <= 47))
				i++;
		}
		while (line[i] && line[i] != '$')
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
			}
			buf[j++] = line[i++];
		}
		str = join_dol(str, buf, j);
		free(buf);
		j = 0;
	}
	return (str);
}
