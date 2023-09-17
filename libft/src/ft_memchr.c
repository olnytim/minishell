/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:14:06 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/17 20:40:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)

{
	char	*cop;
	char	d;
	size_t	l;

	(void)l;
	if (n == 0)
		return (NULL);
	d = (char)c;
	cop = (char *)s;
	l = ft_strlen(cop);
	while (--n)
	{
		if (*cop != d)
		{
			cop++;
			l--;
		}
		if (*cop == d || n == 0)
			break ;
	}
	if (*cop != d)
		return (NULL);
	return ((void *) cop);
}
