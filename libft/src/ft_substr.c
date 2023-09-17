/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:27:14 by timelkon          #+#    #+#             */
/*   Updated: 2023/05/31 16:14:25 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	char	*st;
	char	*spc;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	st = (char *)s;
	spc = malloc(len + 1);
	if (!spc)
		return (0);
	i = 0;
	while (i != len)
	{
		spc[i] = st[start];
		i++;
		start++;
	}
	spc[i] = '\0';
	return (spc);
}
