/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:14:34 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/31 17:16:40 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_linked_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("Key: %s, Val: %s\n", current->key, current->val);
		current = current->next;
	}
}

void	print2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
