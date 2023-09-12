/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:10:57 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/09 19:39:41 by user             ###   ########.fr       */
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
	g_exit_code = 1;
}

void	ft_sigquit(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
	g_exit_code = 131;
}

// void	ft_sigempty(int sig)
// {
// 	(void)sig;
// 	printf("");
// }

void	ft_sigline(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_code = 130;
}

void	sig_event_loop(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_next_line);
	signal(SIGQUIT, SIG_IGN);
}
