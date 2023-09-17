/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:47:01 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/01 12:43:45 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s1, char (*f)(unsigned int, char))

{
	char	*s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	s = ft_strdup(s1);
	if (!s)
		return (NULL);
	while (s[i])
	{
	s[i] = (*f)(i, s[i]);
	i++;
	}
	s[i] = '\0';
	return (s);
}
