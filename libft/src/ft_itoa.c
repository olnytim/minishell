/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:29:26 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nbr(int n, char *s, int n1)

{
	int	i;

	i = n1;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	s[i] = '\0';
	i--;
	if (n == 0)
	{
		s[0] = '0';
		return (s);
	}
	while (i >= 0 && n > 0)
	{
		s[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (s);
}

char	*ft_itoa(int n1)

{
	unsigned int	n;
	char			*s;

	if (n1 == 0)
		return (ft_strdup("0"));
	if (n1 == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n1 == 2147483647)
		return (ft_strdup("2147483647"));
	n = ft_numlen((unsigned int)n1);
	s = malloc(n * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	s = nbr(n1, s, n);
	return (s);
}
