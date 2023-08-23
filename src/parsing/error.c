/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:45 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/19 17:34:53 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*error(int e)
{
	if (e == 0)
		write(2, "error: please close the quote\n", 31);
	else if (e == 1)
		write(2, "error: no command after '|'\n", 28);
	else if (e == 2)
		write(2, "syntax error near unexpected token\n", 37);
	return (0);
}
