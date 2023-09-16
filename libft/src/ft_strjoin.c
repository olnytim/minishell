/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:40:03 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/01 12:43:36 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)

{
	char	*str1;
	char	*str2;
	char	*spc;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	str1 = (char *)s1;
	str2 = (char *)s2;
	spc = malloc (ft_strlen(str1) + ft_strlen(str2) * sizeof(char) + 1);
	if (spc == NULL)
		return (NULL);
	while (*str1)
		spc[i++] = *str1++;
	while (*str2)
	{
		spc[i] = *str2;
		i++;
		str2++;
	}
	spc[i] = '\0';
	return (spc);
}
