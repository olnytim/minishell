/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:55:54 by timelkon          #+#    #+#             */
/*   Updated: 2023/01/27 19:41:18 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	char	*cop;
	int		num;

	cop = (char *)s;
	num = ft_strlen(cop);
	while (*cop != '\0')
		cop++;
	while (num >= 0)
	{
		if (*cop == (char)c)
			return (cop);
		cop--;
		num--;
	}
	return (0);
}
