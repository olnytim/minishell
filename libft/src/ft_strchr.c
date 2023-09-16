/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:41:07 by timelkon          #+#    #+#             */
/*   Updated: 2023/02/16 12:20:16 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)

{
	char	*cop;

	cop = (char *)s;
	while (*cop != '\0' && *cop != (char)c)
		cop++;
	if (*cop == (char)c)
		return (cop);
	return (0);
}
