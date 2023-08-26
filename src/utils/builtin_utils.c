/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:24:02 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/26 14:37:04 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cmp(char *cmd)
{
	if (!*cmd || !cmd)
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
int		check_builtin(t_parse *cmd, t_data *data)
{
	if (!*cmd->cmd)
		return (0);
    if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0
        && ft_strncmp(cmd->cmd[0], "pwd", ft_strlen(cmd->cmd[0])) == 0)
        return (pwd(), close(cmd->fd), 1);
    else if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0
        && ft_strncmp(cmd->cmd[0], "echo", ft_strlen(cmd->cmd[0])) == 0)
        return (echo(cmd->cmd), close(cmd->fd), 1);
    else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0
        && ft_strncmp(cmd->cmd[0], "unset", ft_strlen(cmd->cmd[0])) == 0)
        return (unset(data, cmd), close(cmd->fd), 1);
    else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0
        && ft_strncmp(cmd->cmd[0], "export", ft_strlen(cmd->cmd[0])) == 0)
        return (export(data, cmd), close(cmd->fd), 1);
    else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0
        && ft_strncmp(cmd->cmd[0], "env", ft_strlen(cmd->cmd[0])) == 0)
        return (env(data), close(cmd->fd), 1);
	else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0
		&& ft_strncmp(cmd->cmd[0], "exit", ft_strlen(cmd->cmd[0])) == 0)
		return (ft_exit(cmd), close(cmd->fd), 1);
    
    // else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0
    //  && ft_strncmp(cmd->cmd[0], "cd", ft_strlen(cmd->cmd[0])) == 0)
    //  return (cd(cmd->cmd), close(cmd->fd), 1);
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
