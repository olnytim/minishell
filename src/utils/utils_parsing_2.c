/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:26:31 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/04 17:48:13 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		input_node = input_node->next;
		// if (temp->t_tig)
		// 	free(temp->t_tig);
		// free(temp);
		temp = NULL;
	}
}

void	free_input(t_parse *input_var, t_parse *input_node)
{
	t_parse	*temp;

	(void)input_node;
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
	// free_node(input_node);
}
