/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:14:34 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/17 18:42:26 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_linked_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (!*current->key && !*current->val)
			printf("%s", current->key);
		else if (*current->key && *current->val)
			printf("%s=%s\n", current->key, current->val);
		else if (current->flag == 1)
			printf("%s=\n", current->key);
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
