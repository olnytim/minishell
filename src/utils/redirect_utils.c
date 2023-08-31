/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:24:53 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/31 18:56:06 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_dup(t_parse *lst, int status)
{
	if (status == 1 || status == 2)
		dup2(lst->fd, STDIN_FILENO);
	else if (status == 3 || status == 4)
		dup2(lst->fd, STDOUT_FILENO);
}

void	ft_redirect_cmp(t_parse *lst, int *status)
{
	if (**lst->operator == '<' && *(*lst->operator + 1) != '<')
	{
		if (!ft_redirect_in(lst))
			*status = 1;
		else
			*status = -1;
		lst->file++;
	}
	else if (**lst->operator == '<' && *(*lst->operator + 1) == '<')
	{
		*status = ft_redirect_heredoc(lst);
		lst->lim++;
	}
	else if (**lst->operator == '>' && *(*lst->operator + 1) != '>')
	{
		*status = ft_redirect_out(lst);
		lst->file++;
	}
	else if (**lst->operator == '>' && *(*lst->operator + 1) == '>')
	{
		*status = ft_redirect_out_append(lst);
		lst->file++;
	}
}
