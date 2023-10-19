/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:22:44 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:23:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_t_parse(t_parse *lst)
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

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_node(t_parse *input_node)
{
	t_parse	*temp;

	while (input_node)
	{
		temp = input_node;
		temp->operator = NULL;
		temp->cmd = NULL;
		temp->file = NULL;
		temp->lim = NULL;
		temp->t_tig = NULL;
		input_node = input_node->next;
		free(temp);
		temp = NULL;
	}
}

void	free_input(t_parse *input_var, t_parse *input_node)
{
	t_parse	*temp;

	while (input_var)
	{
		temp = input_var;
		free2d(temp->operator);
		free2d(temp->cmd);
		free2d(temp->file);
		free2d(temp->lim);
		free(temp->t_tig);
		temp->t_tig = NULL;
		input_var = input_var->next;
		free(temp);
		temp = NULL;
	}
	free_node(input_node);
}
