/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:56:32 by apiloian          #+#    #+#             */
/*   Updated: 2023/09/14 15:04:28 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
	g_exit_code = 0;
}

void	unset(t_data *data, char **argv)
{
	t_env	*lst;

	lst = data->env_lst;
	while (lst->next && ft_strncmp(lst->key, argv[1], ft_strlen(argv[1])) != 0)
	{
		if (lst->next->next
			&& ft_strncmp(lst->next->key, argv[1], ft_strlen(argv[1])) == 0)
		{
			lst->next = lst->next->next;
			break ;
		}
		lst = lst->next;
	}
	data->env = join_key_and_val(data->env_lst);
	g_exit_code = 0;
}

void	echo(char **args)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (ft_strncmp(args[i] + j, "n", ft_strlen(args[i] + j)) != 0)
			break ;
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	g_exit_code = 0;
}

void	env(t_data *data)
{
	print2d(data->env);
	g_exit_code = 0;
}
