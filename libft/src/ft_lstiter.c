/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:52:56 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/02 14:42:58 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))

{
	t_list	*a;

	if (!lst || !f)
		return ;
	a = lst;
	while (a)
	{
		(*f)(a -> content);
		a = a -> next;
	}
}
