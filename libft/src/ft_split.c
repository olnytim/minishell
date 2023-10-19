/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:20:47 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **s, int i)

{
	while (i--)
		free(s[i]);
	free(s);
}

int	countsplit(int i, int w, char *s, char c)

{
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			w++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
		{
			while (s[i] == c)
				i++;
		}
	}
	return (w);
}

char	**delai(int i, int e, char *s, char c)

{
	int		start;
	char	**split;

	split = malloc ((countsplit(0, 0, s, c) + 1) * sizeof (char *));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			split[e] = ft_substr(s, start, (i - start));
			if (split[e] == NULL)
			{
				ft_free (split, e);
				return (0);
			}
		}
		e++;
	}
	return (split);
}

char	**ft_split(char const *s1, char c)

{
	char	*s;
	char	**split;

	if (!s1)
		return (NULL);
	s = (char *)s1;
	split = delai(0, 0, s, c);
	if (!split)
		return (NULL);
	split[countsplit(0, 0, s, c)] = 0;
	return (split);
}
