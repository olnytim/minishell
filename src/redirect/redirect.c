/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:41:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/11 18:30:15 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_out(t_parse *lst)
{
	int	i;

	i = 0;
	while (lst->file[i])
		lst->fd = open(lst->file[i++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(lst->fd, STDOUT_FILENO);
}

void	ft_redirect_out_append(t_parse *lst)
{
	int	i;

	i = 0;
	while (lst->file[i])
		lst->fd = open(lst->file[i++], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(lst->fd, STDOUT_FILENO);
}

void	ft_redirect_in(t_parse *lst)
{
	int	i;

	i = 0;
	while (lst->file[i])
		lst->fd = open(lst->file[i++], O_RDONLY);
	dup2(lst->fd, STDIN_FILENO);
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
		if (ft_strncmp(lim, str, ft_strlen(str) - 1) == 0
			&& ft_strncmp(lim, str, ft_strlen(lim)) == 0)
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

void	ft_redirect(t_parse *lst)
{
	if (ft_strncmp(*lst->operator, ">", ft_strlen(*lst->operator)) == 0
		&& ft_strncmp(*lst->operator, ">", 1) == 0)
		ft_redirect_out(lst);
	else if (ft_strncmp(*lst->operator, ">>", ft_strlen(*lst->operator)) == 0
		&& ft_strncmp(*lst->operator, ">>", 2) == 0)
		ft_redirect_out_append(lst);
	else if (ft_strncmp(*lst->operator, "<", ft_strlen(*lst->operator)) == 0
		&& ft_strncmp(*lst->operator, "<", 1) == 0)
		ft_redirect_in(lst);
	else if (ft_strncmp(*lst->operator, "<<", ft_strlen(*lst->operator)) == 0
		&& ft_strncmp(*lst->operator, "<<", 2) == 0)
		ft_redirect_heredoc(lst);
}
