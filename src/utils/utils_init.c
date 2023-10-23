/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:24:34 by apiloian          #+#    #+#             */
/*   Updated: 2023/10/23 19:05:01 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cont_1(t_data *data, t_parse *input, char *str)
{
	t_parse	*input_free;

	data->env = join_key_and_val(data->env_lst);
	data->path = find_path(data->env);
	input_free = duble_pointers(input);
	conditions(input, data);
	unlink("heredoc");
	data->join_path = NULL;
	if (*str)
		add_history(str);
	free2d(data->env);
	free_input(input_free, input);
	free(str);
}

void	exit_message_for_5051(char *cmd)
{
	printf("5051: %s: No such file or directory\n", cmd);
	exit(EXIT_FAILURE);
}
