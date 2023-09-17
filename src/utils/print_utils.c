/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:14:34 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/16 21:44:42 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_linked_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (*current->key && *current->val)
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
