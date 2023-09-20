/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:12:42 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)

{
	char	*spc;
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	str = (char *)s1;
	spc = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (!spc)
		return (NULL);
	while (str[i] != '\0')
	{
		spc[i] = str[i];
		i++;
	}
	spc[i] = '\0';
	return (spc);
}
