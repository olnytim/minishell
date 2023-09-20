/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:17:32 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:24:37 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back_shell(t_parse **lst, t_parse *new)
{
	t_parse	*a;

	a = (*lst);
	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			(*lst)->next = NULL;
			(*lst)->prev = NULL;
			return ;
		}
		while (a -> next != NULL)
			a = a -> next;
		a -> next = new;
		new->prev = a;
	}
}

char	*ft_strjoin_nl(char *str1, char *str2)
{
	char	*spc;
	size_t	i;

	i = 0;
	spc = malloc (ft_strlen(str1) + ft_strlen(str2) * sizeof(char) + 1);
	if (spc == NULL)
		return (NULL);
	while (str1 && str1[i])
	{
		spc[i] = str1[i];
		i++;
	}
	while (str2 && *str2)
	{
		spc[i] = *str2;
		i++;
		str2++;
	}
	spc[i] = '\0';
	return (spc);
}

void	file_lim_quotes_2(char *arg, int *i, int *j, char *buf)
{
	char	q;

	q = arg[*i];
	*i += 1;
	while (arg[*i] != q)
	{
		buf[*j] = arg[*i];
		*i += 1;
		*j += 1;
	}
	*i += 1;
	if (arg[*i] == 34 || arg[*i] == 39)
		file_lim_quotes_2(arg, i, j, buf);
}

char	*file_lim_quotes(char *arg, int *i, int j)
{
	char	*str;
	char	*buf;

	buf = malloc(ft_strlen(arg) + 1);
	while (arg[*i] && arg[*i] != ' ' && arg[*i] != '\t'
		&& arg[*i] != '>' && arg[*i] != '|' && arg[*i] != '<')
	{
		if (arg[*i] == 34 || arg[*i] == 39)
			file_lim_quotes_2(arg, i, &j, buf);
		if (arg[*i] == ' ' || arg[*i] == '\t')
			break ;
		buf[j++] = arg[*i];
		if (arg[*i])
			*i += 1;
	}
	buf[j] = '\0';
	str = ft_strdup(buf);
	free(buf);
	return (str);
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
	if (line[*i] == 34 || line[*i] == 39)
		quote_handle(line, buf, i, j);
}
