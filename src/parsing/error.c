/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:45 by timelkon          #+#    #+#             */
/*   Updated: 2023/08/27 15:20:21 by user             ###   ########.fr       */
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
		write(2, "syntax error near unexpected token\n", 35);
	return (0);
}
