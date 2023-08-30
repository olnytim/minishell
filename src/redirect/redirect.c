/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:41:18 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/30 13:43:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redirect_in(t_parse *lst)
{
	lst->fd = open(*lst->file, O_RDONLY);
	if (lst->fd == -1)
	{
		close(lst->fd);
		printf("ebash: %s: No such file or directory\n", *lst->file);
		return (1);
	}
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
		str = readline("> ");
		if (!str || (ft_strncmp(lim, str, ft_strlen(str)) == 0
			&& ft_strncmp(lim, str, ft_strlen(lim)) == 0))
		{
			free(str);
			break ;
		}
		write(lst->fd, str, ft_strlen(str));
		if (*str != '\n')
			write(lst->fd, "\n", 1);
		free(str);
	}
	close(lst->fd);
	lst->fd = open("heredoc", O_RDONLY);
}

void	ft_redirect_out(t_parse *lst)
{
	lst->fd = open(*lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_redirect_out_append(t_parse *lst)
{
	lst->fd = open(*lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	ft_redirect(t_parse *lst)
{
	int	status;
	
	if (!lst->operator || !*lst->operator)
		return (0);
	while (*lst->operator)
	{
		if (**lst->operator == '<' && *(*lst->operator + 1) != '<')
		{
			if (!ft_redirect_in(lst))
				status = 1;
			lst->file++;
		}
		else if (**lst->operator == '<' && *(*lst->operator + 1) == '<')
		{
			ft_redirect_heredoc(lst);
			lst->lim++;
			status = 2;
		}
		else if (**lst->operator == '>' && *(*lst->operator + 1) != '>')
		{
			ft_redirect_out(lst);
			lst->file++;
			status = 3;
		}
		else if (**lst->operator == '>' && *(*lst->operator + 1) == '>')
		{
			ft_redirect_out_append(lst);
			lst->file++;
			status = 4;
		}
		lst->operator++;
	}
	return (status);
}

void	ft_redirect_dup(t_parse *lst, int status)
{
	if (status == 1 || status == 2)
		dup2(lst->fd, STDIN_FILENO);
	else if (status == 3 || status == 4)
		dup2(lst->fd, STDOUT_FILENO);
}
