/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:41:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/05 21:47:35 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_out(t_parse *lst)
{
	lst->fd = open(lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(lst->fd, STDOUT_FILENO);
}

void	ft_redirect_out_append(t_parse *lst)
{
	lst->fd = open(lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(lst->fd, STDOUT_FILENO);
}

void	ft_redirect_in(t_parse *lst)
{
	lst->fd = open(lst->file, O_RDONLY);
	dup2(lst->fd, STDIN_FILENO);
}

void	ft_redirect_heredoc(t_parse *lst)
{
	
}

void	ft_redirect(t_parse *lst)
{
	if (ft_strncmp(lst->operator, ">", ft_strlen(lst->operator)) == 0
		&& ft_strncmp(lst->operator, ">", 1) == 0)
		ft_redirect_out(lst);
	else if (ft_strncmp(lst->operator, ">>", ft_strlen(lst->operator)) == 0
		&& ft_strncmp(lst->operator, ">>", 2) == 0)
		ft_redirect_out_append(lst);
	else if (ft_strncmp(lst->operator, "<", ft_strlen(lst->operator)) == 0
		&& ft_strncmp(lst->operator, "<", 1) == 0)
		ft_redirect_in(lst);
	else if (ft_strncmp(lst->operator, "<<", ft_strlen(lst->operator)) == 0
		&& ft_strncmp(lst->operator, "<<", 2) == 0)
		ft_redirect_heredoc(lst);
}
