/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:27:09 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

{
	char	*str;
	char	*to_find;
	size_t	a;
	size_t	b;

	a = 0;
	str = (char *)haystack;
	to_find = (char *)needle;
	if (ft_strlen(to_find) == 0)
		return (str);
	if (!str && len == 0)
		return (0);
	while (str[a])
	{
		b = 0;
		while (str[a + b] == to_find[b] && to_find[b] != '\0' && (a + b) < len)
			b++;
		if (to_find[b] == '\0')
			return (&str[a]);
		a++;
	}
	return (0);
}
