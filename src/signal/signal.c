/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:10:57 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/16 19:26:23 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_next_line(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
