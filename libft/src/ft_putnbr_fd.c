/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:34:43 by timelkon          #+#    #+#             */
/*   Updated: 2023/01/27 19:13:54 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnum(char c, int fd)

{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)

{
	if (n == -2147483648)
	{
		putnum('-', fd);
		putnum('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		putnum('-', fd);
		n *= -1;
	}
	if (n / 10 > 0)
	{
		ft_putnbr_fd(n / 10, fd);
		putnum((n % 10) + 48, fd);
	}
	if (n <= 9)
		putnum(n + 48, fd);
}
