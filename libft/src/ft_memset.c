/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:41:09 by timelkon          #+#    #+#             */
/*   Updated: 2023/01/27 19:11:49 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)

{
	size_t	a;
	char	*str;

	str = (char *) b;
	a = 0;
	if (len > 0)
	{
		while (a != len)
		{
			str[a] = (unsigned char)c;
			a++;
		}
	}
	return (str);
}
