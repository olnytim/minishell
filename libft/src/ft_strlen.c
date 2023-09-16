/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:01:13 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/16 16:16:25 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;
	char	*len;

	if (!str)
		return (0);
	a = 0;
	len = (char *)str;
	while (len[a] != '\0')
	{
		a++;
	}
	return (a);
}
