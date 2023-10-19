/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:37:31 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:18 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redirect_in(t_parse *lst)
{
	lst->fd_in = open(*lst->file, O_RDONLY);
	if (lst->fd_in == -1)
	{
		close(lst->fd_in);
		printf("ebash: %s: No such file or directory\n", *lst->file);
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

int	ft_redirect_heredoc(t_parse *lst)
{
	char	*str;
	char	*lim;

	lim = *lst->lim;
	lst->fd_in = open("heredoc", O_RDWR | O_CREAT, 0644);
	while (1)
	{
		str = readline("> ");
		if (!str || (ft_strncmp(lim, str, ft_strlen(str)) == 0
				&& ft_strncmp(lim, str, ft_strlen(lim)) == 0))
		{
			free(str);
			break ;
		}
		write(lst->fd_in, str, ft_strlen(str));
		if (*str != '\n')
			write(lst->fd_in, "\n", 1);
		free(str);
	}
	close(lst->fd_in);
	lst->fd_in = open("heredoc", O_RDONLY);
	return (2);
}

int	ft_redirect_out(t_parse *lst)
{
	lst->fd_out = open(*lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (3);
}

int	ft_redirect_out_append(t_parse *lst)
{
	lst->fd_out = open(*lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (4);
}

int	ft_redirect(t_parse *lst)
{
	int	status;

	status = 0;
	if (!lst->operator || !*lst->operator)
		return (0);
	while (*lst->operator)
	{
		ft_redirect_cmp(lst, &status);
		if (status == -1)
			return (status);
		lst->operator++;
	}
	return (status);
}
