/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:51:39 by timelkon          #+#    #+#             */
/*   Updated: 2023/01/27 19:14:24 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)

{
	int	a;

	a = 0;
	if (!s)
		return ;
	while (s[a] != '\0')
	{
		write(fd, &s[a], 1);
		a++;
	}
}
