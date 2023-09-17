/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:09:52 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/02 14:48:16 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)

{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			a;

	a = 0;
	if (!dst && !src)
		return (0);
	str1 = (unsigned char *) dst;
	str2 = (unsigned char *) src;
	if (!n && str1 == str2)
		return (str1);
	while (n)
	{
		str1[a] = str2[a];
		a++;
		n--;
	}
	return (str1);
}
