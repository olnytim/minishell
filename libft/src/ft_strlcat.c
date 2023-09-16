/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:51:55 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/02 14:57:57 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t size)

{
	size_t	dstlen;
	size_t	srclen;
	size_t	cnt;
	size_t	b;

	b = 0;
	cnt = size;
	srclen = ft_strlen(src);
	if (dst == 0 && size == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (size <= dstlen || size == 0)
		return (srclen + size);
	while (*dst && cnt != 0)
	{
		dst++;
		cnt--;
	}
	if (cnt > 0)
	{
		while (b < size - dstlen - 1 && src[b] != '\0')
			*dst++ = src[b++];
	*dst = '\0';
	}
	return (dstlen + srclen);
}
