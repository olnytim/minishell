/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:36:58 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/10 13:26:33 by apiloian         ###   ########.fr       */
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
	size_t	i;

	i = 0;
	str = ft_strdup("");
	while (arr[i])
	{
		str = ft_strjoin(str, arr[i]);
		if (arr[i + 1])
			str = ft_strjoin(str, " ");
		++i;
	}
	return (str);
}

char	**struct_to2arr(t_parse *lst)
{
	char	**arr;
	size_t	size;
	size_t	i;

	size = ft_parse_size(lst);
	arr = malloc(sizeof(char *) * (size + 1) + 3);
	if (!arr)
		return (NULL);
	i = 0;
	arr[i++] = ft_strdup("minishell");
	arr[i++] = ft_strdup("/dev/stdin");
	while (lst)
	{
		// dprintf(2, "cmd: %s\n", join_2d_arr(lst->cmd));
		arr[i] = ft_strdup(join_2d_arr(lst->cmd));
		lst = lst->next;
		++i;
	}
	arr[i++] = ft_strdup("/dev/stdout");
	arr[i] = NULL;
	return (arr);
}
