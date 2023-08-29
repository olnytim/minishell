/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:17:32 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/29 16:03:36 by timelkon         ###   ########.fr       */
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
	while (*str2)
	{
		spc[i] = *str2;
		i++;
		str2++;
	}
	spc[i] = '\0';
	// free(str1);
	return (spc);
}
