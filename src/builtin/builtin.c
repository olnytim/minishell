/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:56:32 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/01 14:04:34 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
}

void	unset(t_data *data, t_parse *pars)
{
	t_env	*lst;
	int		i;

	i = 1;
	while (pars->cmd[i])
	{
		valid_variable_name(pars->cmd[i]);
		lst = data->env_lst;
		while (lst->next && ft_strncmp(lst->key, pars->cmd[i],
				ft_strlen(pars->cmd[i])) != 0)
		{
			if (lst->next->next && ft_strncmp(lst->next->key, pars->cmd[i],
					ft_strlen(pars->cmd[i])) == 0)
			{
				lst->next = lst->next->next;
				break ;
			}
			lst = lst->next;
		}
		i++;
	}
	data->env = join_key_and_val(data->env_lst);
}

void	echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}

void	env(t_data *data)
{
	print2d(data->env);
}
