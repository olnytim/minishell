/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:01:41 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst1, const void *src1, size_t len)

{
	char	*dst;
	char	*src;
	size_t	i;

	i = 0;
	dst = (char *) dst1;
	src = (char *) src1;
	if (dst < src)
	{
		while (i < len)
		{
		dst[i] = src[i];
		i++;
		}
	}
	else if (dst > src)
	{
		i = len - 1;
		while (i < len)
		{
			dst[i] = src[i];
			i--;
		}
	}
	return (dst);
}
