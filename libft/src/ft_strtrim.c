/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:33:15 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)

{
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (0);
	if (!*s)
		return (ft_strdup(""));
	j = ft_strlen(s);
	while (s[i] && ft_strchr(set, s[i]))
		i++;
	while (j > i && ft_strchr(set, s[j]))
		j--;
	return (ft_substr(s, i, (j - i + 1)));
}
