/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:14:56 by olnytim           #+#    #+#             */
/*   Updated: 2023/07/25 16:54:17 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_beg	*begin;
	(void)ac;
	(void)av;

	begin = malloc(sizeof(t_beg));
	while (1)
	{
		// ft_prompt();
		begin->input = readline("$> ");
		printf("input is: %s\n", begin->input);
		add_history(begin->input);
	}
	return (0);
}
