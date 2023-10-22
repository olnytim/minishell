/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:24:53 by apiloian          #+#    #+#             */
/*   Updated: 2023/10/22 19:16:53 by mac              ###   ########.fr       */
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

int	ft_input_cmp(t_parse *lst, int *status, t_data *data)
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
			*status = ft_redirect_heredoc(lst, data) + 3;
		else
			*status = ft_redirect_heredoc(lst, data);
		lst->lim++;
		return (0);
	}
	return (1);
}

void	ft_redirect_cmp(t_parse *lst, int *status, t_data *data)
{
	if (ft_input_cmp(lst, status, data) && **lst->operator == '>'
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
