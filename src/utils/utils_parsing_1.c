/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:17:32 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/22 13:06:13 by timelkon         ###   ########.fr       */
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
