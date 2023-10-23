/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:45 by apiloian          #+#    #+#             */
/*   Updated: 2023/10/23 18:21:30 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*error(int e)
{
	if (e == 0)
		write(2, "error: please close the quote\n", 31);
	else if (e == 1)
		write(2, "syntax error near unexpected token '|'\n", 39);
	else if (e == 2)
		write(2, "syntax error near unexpected token\n", 35);
	else if (e == 3)
		write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 109);
	g_exit_code = 258;
	return (0);
}
