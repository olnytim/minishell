/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:12:37 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/03 18:29:47 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_free(char **s, int i)

{
	while (i--)
		free(s[i]);
	free(s);
}

int	quote_check(char *s, int i)
{
	if (s[i++] == 34)
	{
		while (s[i] != 34)
			i++;
	}
	else
	{
		while (s[i++] != 39)
			i++;
	}
	return (i + 1);
}

int	countsplit(int i, int w, char *s)
{
	while (s[i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == 34 || s[i] == 39)
		{
			if (s[i] == '<')
			{
				if (s[i + 1] == '<')
					i++;
				i++;
			}
			else if (s[i] == '>')
			{
				if (s[i + 1] == '>')
					i++;
				i++;
			}
			else if (s[i] == '|')
				i++;
			else if	(s[i] == 34 || s[i] == 39)
				i = quotes_check(s, i);
		}
		else
			while (s[i] != '<' && s[i] != '>' && s[i] != '|' && s[i] != 34 && s[i] != 39)
				i++;
		w++;
	}
	return (w);
}

char	**delai(int i, int e, char *s)
{
	int		start;
	char	**split;

	split = malloc ((countsplit(0, 0, s) + 1) * sizeof (char *));
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

char	**smart_split(char *line)
{
	char	**split;

	if (!line)
		return (NULL);
	split = delai(0, 0, line);
	if (!split)
		return (NULL);
	split[countsplit(0, 0, s, c)] = 0;
	return (split);
}
