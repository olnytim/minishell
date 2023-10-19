/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:24:53 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/20 21:24:27 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_dup(t_parse *lst, int status)
{
	if (status == 1 || status == 2)
		dup2(lst->fd_in, STDIN_FILENO);
	else if (status == 3 || status == 4)
		dup2(lst->fd_out, STDOUT_FILENO);
	else if (status == 5)
	{
		dup2(lst->fd_in, STDIN_FILENO);
		dup2(lst->fd_out, STDOUT_FILENO);
	}
}

int	ft_input_cmp(t_parse *lst, int *status)
{
	if (**lst->operator == '<' && *(*lst->operator + 1) != '<')
	{
		if (!ft_redirect_in(lst))
		{
			if (*status == 3 || *status == 4 || *status == 5)
				*status = 5;
			else
				*status = 1;
		}
		else
			*status = -1;
		lst->file++;
		return (0);
	}
	else if (**lst->operator == '<' && *(*lst->operator + 1) == '<')
	{
		if (*status == 3 || *status == 4 || *status == 5)
			*status = ft_redirect_heredoc(lst) + 3;
		else
			*status = ft_redirect_heredoc(lst);
		lst->lim++;
		return (0);
	}
	return (1);
}

void	ft_redirect_cmp(t_parse *lst, int *status)
{
	if (ft_input_cmp(lst, status) && **lst->operator == '>'
		&& *(*lst->operator + 1) != '>')
	{
		if (*status == 1 || *status == 2 || *status == 5)
			*status = ft_redirect_out(lst) + 2;
		else
			*status = ft_redirect_out(lst);
		lst->file++;
	}
	else if (**lst->operator == '>' && *(*lst->operator + 1) == '>')
	{
		if (*status == 1 || *status == 2 || *status == 5)
			*status = ft_redirect_out_append(lst) + 1;
		else
			*status = ft_redirect_out_append(lst);
		lst->file++;
	}
}
