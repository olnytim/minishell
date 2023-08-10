/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:24:02 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/10 17:00:51 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(t_parse *lst, t_data *data)
{
	// char	**args;

	// args = ft_split(lst->cmd, ' ');
	if (ft_strncmp(lst->cmd[0], "pwd", 3) == 0
		&& ft_strncmp(lst->cmd[0], "pwd", ft_strlen(lst->cmd[0])) == 0)
		return (pwd(), close(lst->fd), 1);
	else if (ft_strncmp(lst->cmd[0], "echo", 4) == 0
		&& ft_strncmp(lst->cmd[0], "echo", ft_strlen(lst->cmd[0])) == 0)
		return (echo(lst->cmd), close(lst->fd), 1);
	else if (ft_strncmp(lst->cmd[0], "unset", 5) == 0
		&& ft_strncmp(lst->cmd[0], "unset", ft_strlen(lst->cmd[0])) == 0)
		return (unset(data, lst->cmd), close(lst->fd), 1);
	else if (ft_strncmp(lst->cmd[0], "env", 3) == 0
		&& ft_strncmp(lst->cmd[0], "env", ft_strlen(lst->cmd[0])) == 0)
		return (env(data), close(lst->fd), 1);
	
	// else if (ft_strncmp(lst->cmd[0], "cd", 2) == 0
	// 	&& ft_strncmp(lst->cmd[0], "cd", ft_strlen(lst->cmd[0])) == 0)
	// 	return (cd(lst->cmd), close(lst->fd), 1);
	return (0);
}
