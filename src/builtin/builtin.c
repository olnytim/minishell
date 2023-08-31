/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:56:32 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/31 17:57:31 by valeriafedo      ###   ########.fr       */
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
	int		b;

	i = 1;
	while(pars->cmd[i])
	{
		b = 0;
		while (pars->cmd[i][b] == '_')
			b++;
		if (b == 0)
		{
			while(pars->cmd[i][b])
			{
				if (ft_isalpha(pars->cmd[i][b++]) == 0 && ft_isdigit(pars->cmd[i][0]) == 0)
				{
					// if (ft_isdigit(pars->cmd[i][b]) == 0)
					// {
					// 	write(2, "syntax error near unexpected token\n", 35);
					// 	return ;
					// }
					write(2, "syntax error near unexpected token\n", 35);
					return ;
				}
			}
		}
		b = 0;
		if (ft_isalpha(pars->cmd[i][b]) == 0 && pars->cmd[i][0] != '_')
		{
			write(2, "unset: not a valid identifier\n", 30);
			b++;
			return ;
		}
		lst = data->env_lst;
		while (lst->next && ft_strncmp(lst->key, pars->cmd[i], ft_strlen(pars->cmd[i]))!= 0)
		{
			if (lst->next->next && ft_strncmp(lst->next->key, pars->cmd[i], ft_strlen(pars->cmd[i]))== 0)
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
	// i am working on this
	//i shodl work on this i think
	// this takes time
	// Lera you are the best
	
}

void	env(t_data *data)
{
	print2d(data->env);
}
