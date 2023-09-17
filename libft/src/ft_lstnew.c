/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:10:50 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/02 14:44:44 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)

{
	t_list	*frs;

	frs = malloc(sizeof(t_list));
	if (!frs)
		return (0);
	frs -> next = NULL;
	frs -> content = content;
	return (frs);
}
