/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:26:18 by vfedorov          #+#    #+#             */
/*   Updated: 2023/08/21 15:18:49 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int check_builtin(t_parse *lst, t_data *data)
{
    // char **args;

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
