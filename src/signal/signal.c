/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:10:57 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/15 20:17:47 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_next_line(int sig)
{
	(void)sig;
	printf("\n");
	printf(MINISHELL);
}

void	ft_nothing(int sig)
{
	(void)sig;
}

void	sig_event_loop(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_next_line);
	signal(SIGQUIT, ft_nothing);
}
