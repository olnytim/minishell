/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:36:58 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/15 11:48:30 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_size(t_parse *lst)
{
	size_t	counter;

	counter = 0;
	while (lst)
	{
		lst = lst->next;
		++counter;
	}
	return (counter);
}

char	*join_2d_arr(char **arr)
{
	char	*str;
	char	*tmp;
	size_t	i;

	i = 0;
	str = ft_strdup("");
	while (arr[i])
	{
		tmp = ft_strjoin(str, arr[i]);
		free(str);
		if (arr[i + 1])
		{
			str = ft_strjoin(tmp, " ");
			free(tmp);
		}
		else
		{
			str = ft_strdup(tmp);
			free(tmp);
		}
		++i;
	}
	return (str);
}

char	**struct_to2arr(t_parse *lst)
{
	char	**arr;
	char	*str;
	size_t	size;
	size_t	i;

	size = ft_parse_size(lst);
	arr = malloc(sizeof(char *) * (size + 4));
	if (!arr)
		return (NULL);
	i = 0;
	arr[i++] = ft_strdup("minishell");
	arr[i++] = ft_strdup("/dev/stdin");
	while (lst)
	{
		str = join_2d_arr(lst->cmd);
		arr[i] = ft_strdup(str);
		free(str);
		lst = lst->next;
		++i;
	}
	arr[i++] = ft_strdup("/dev/stdout");
	arr[i] = NULL;
	return (arr);
}

int	check_pipe(t_parse *input)
{
	int	i;

	i = 0;
	while (input->operator && input->operator[i])
	{
		if (*input->operator[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdir(const char *name)
{
	DIR	*directory;

	directory = opendir(name);
	if (directory != NULL)
	{
		closedir(directory);
		return (0);
	}
	return (-1);
}
