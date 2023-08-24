/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:41:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/24 14:38:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_out(t_parse *lst)
{
	lst->fd = open(*lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(lst->fd, STDOUT_FILENO);
}

void	ft_redirect_out_append(t_parse *lst)
{
	lst->fd = open(*lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(lst->fd, STDOUT_FILENO);
}

int	ft_redirect_in(t_parse *lst)
{
	lst->fd = open(*lst->file, O_RDONLY);
	if (lst->fd == -1)
	{
		close(lst->fd);
		printf("ebash: %s: No such file or directory\n", *lst->file);
		return (1);
	}
	dup2(lst->fd, STDIN_FILENO);
	return (0);
}

void	ft_redirect_heredoc(t_parse *lst)
{
	char	*str;
	char	*lim;

	lim = *lst->lim;
	lst->fd = open("heredoc", O_RDWR | O_CREAT, 0644);
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str || (ft_strncmp(lim, str, ft_strlen(str) - 1) == 0
			&& ft_strncmp(lim, str, ft_strlen(lim)) == 0))
		{
			free(str);
			break ;
		}
		write(lst->fd, str, ft_strlen(str));
		free(str);
	}
	close(lst->fd);
	lst->fd = open("heredoc", O_RDONLY);
	dup2(lst->fd, STDIN_FILENO);
}

int	ft_redirect(t_parse *lst)
{
	if (!*lst->operator)
		return (0);
	while (*lst->operator)
	{
		if (ft_strncmp(*lst->operator, "<", ft_strlen(*lst->operator)) == 0
			&& ft_strncmp(*lst->operator, "<", 1) == 0)
		{
			if (ft_redirect_in(lst))
				return (1);
			lst->file++;
		}
		if (ft_strncmp(*lst->operator, "<<", ft_strlen(*lst->operator)) == 0
			&& ft_strncmp(*lst->operator, "<<", 2) == 0)
		{
			ft_redirect_heredoc(lst);
			lst->lim++;
		}
		if (ft_strncmp(*lst->operator, ">", ft_strlen(*lst->operator)) == 0
			&& ft_strncmp(*lst->operator, ">", 1) == 0)
		{
			ft_redirect_out(lst);
			lst->file++;
		}
		if (ft_strncmp(*lst->operator, ">>", ft_strlen(*lst->operator)) == 0
			&& ft_strncmp(*lst->operator, ">>", 2) == 0)
		{
			ft_redirect_out_append(lst);
			lst->file++;
		}
		lst->operator++;
	}
	return (0);
}
