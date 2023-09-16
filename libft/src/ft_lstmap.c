/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:18:23 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/02 14:46:14 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))

{
	t_list	*gog;
	t_list	*new;

	if (!lst || !f || ! del)
		return (0);
	gog = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst -> content));
		if (!new)
		{
			ft_lstclear (&gog, del);
			return (gog);
		}
		ft_lstadd_back (&gog, new);
		lst = lst -> next;
	}
	return (gog);
}
