/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:45 by timelkon          #+#    #+#             */
/*   Updated: 2023/09/01 18:09:06 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*error(int e)
{
	if (e == 0)
		write(2, "error: please close the quote\n", 31);
	else if (e == 1)
		write(2, "error: no command before or after '|'\n", 38);
	else if (e == 2)
		write(2, "syntax error near unexpected token\n", 35);
	return (0);
}
