/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:39 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		znak;
	size_t	res;

	i = 0;
	znak = 1;
	res = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		znak *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] >= 48 && str[i] <= 57)
	{
		while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
		{
			res = (res * 10) + (str[i] - 48);
			i++;
		}
	}
	return (znak * res);
}
