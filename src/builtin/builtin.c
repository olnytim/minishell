/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:56:32 by apiloian          #+#    #+#             */
/*   Updated: 2023/08/16 18:28:28 by vfedorov         ###   ########.fr       */
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
	// (void)argv;
	// (void)data;
	// int	cnt;
	t_env	*lst;
	
	if (pars->cmd == NULL)
		return ;
	lst = data->env_lst;
	while (lst->next && ft_strncmp(lst->key, pars->cmd[1], ft_strlen(pars->cmd[1]))!= 0)
	{
		if (lst->next->next && ft_strncmp(lst->next->key, pars->cmd[1], ft_strlen(pars->cmd[1]))== 0)
		{
			lst->next = lst->next->next;
			break ;
		}
		lst = lst->next;
	}
	data->env = join_key_and_val(data->env_lst);
	// print2d(data->env);
	// printlinkedlist(data->env_lst);
}

void	export(t_data *data, t_parse *pars)
{
	t_env	*lst;
	t_env	*new;
	char	**str;
	// int		i;

	// i = 1;
	if (pars->cmd == NULL)
		return ;
	lst = data->env_lst;
	while (lst->next->next)
		lst = lst->next;
	puts(lst->next->key);
	puts(lst->next->val);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	str = ft_split(pars->cmd[1], '=');
	new->key = str[0];
	new->val = str[1];
	new->next = NULL;
	lst->next = new;
	lst->next->next = NULL;
	// data->env = join_key_and_val(data->env_lst);
}


// void	real_export(t_data *data, char *argv)
// {
		
// }
// void	export(t_data *data, t_parse *pars)
// {
// 	int	i;

// 	i = 0;
// 	while (pars->cmd[++i])
// 		real_export(data, pars->cmd[i]);
// }
// void	cd(char **args)
// {
	
	
// }

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
