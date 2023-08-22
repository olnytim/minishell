/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:24:02 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/17 18:19:21 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cmp(char *cmd)
{
	if (!*cmd)
		return (0);
	if (ft_strncmp(cmd, "pwd", 3) == 0
		&& ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0
		&& ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0
		&& ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0
		&& ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0
		&& ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0
		&& ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0
		&& ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

    // args = ft_split(lst->cmd, ' ');
    if (ft_strncmp(lst->cmd[0], "pwd", 3) == 0
        && ft_strncmp(lst->cmd[0], "pwd", ft_strlen(lst->cmd[0])) == 0)
        return (pwd(), close(lst->fd), 1);
    else if (ft_strncmp(lst->cmd[0], "echo", 4) == 0
        && ft_strncmp(lst->cmd[0], "echo", ft_strlen(lst->cmd[0])) == 0)
        return (echo(lst->cmd), close(lst->fd), 1);
    else if (ft_strncmp(lst->cmd[0], "unset", 5) == 0
        && ft_strncmp(lst->cmd[0], "unset", ft_strlen(lst->cmd[0])) == 0)
        return (unset(data, lst), close(lst->fd), 1);
    else if (ft_strncmp(lst->cmd[0], "export", 6) == 0
        && ft_strncmp(lst->cmd[0], "export", ft_strlen(lst->cmd[0])) == 0)
        return (export(data, lst), close(lst->fd), 1);
    else if (ft_strncmp(lst->cmd[0], "env", 3) == 0
        && ft_strncmp(lst->cmd[0], "env", ft_strlen(lst->cmd[0])) == 0)
        return (env(data), close(lst->fd), 1);
    
    // else if (ft_strncmp(lst->cmd[0], "cd", 2) == 0
    //  && ft_strncmp(lst->cmd[0], "cd", ft_strlen(lst->cmd[0])) == 0)
    //  return (cd(lst->cmd), close(lst->fd), 1);
    return (0);
}

int	check_builtin_with_redirect(t_parse *cmd, t_data *data)
{
	int	child;

	if (*cmd->operator && (cmd->operator[0][0] == '>'
		|| cmd->operator[0][0] == '<'))
	{
		child = fork();
		if (child == 0)
		{
			if (builtin_cmp(cmd->cmd[0]))
			{
				ft_redirect(cmd);
				check_builtin(cmd, data);
			}
			exit(EXIT_SUCCESS);
		}
		return (builtin_cmp(cmd->cmd[0]));
	}
	else
		return (check_builtin(cmd, data));
}
