/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:33:15 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/01 12:44:01 by timelkon         ###   ########.fr       */
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
