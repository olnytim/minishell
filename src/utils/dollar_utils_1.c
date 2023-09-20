/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:13:24 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:23:54 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	desipher_dollar_1(char *line, int i)
{
	if (line[i] == '?' && line[i - 1] == '$')
		return (i + 1);
	while ((line[i] == '?' && line[i - 1] == '$')
		|| (line[i] && line[i] != '$' && line[i] != ' ' && line[i] != 92
			&& line[i] != '=' && line[i] != '@' && line[i] != '\t'
			&& line[i] != '?' && !(line[i] >= 33 && line[i] <= 47)))
		i++;
	return (i);
}
