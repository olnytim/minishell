/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:19:20 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/01 14:25:38 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int unset_forchar(int symbol)
{
	if ((symbol >= 33 && symbol <= 47) || (symbol >= 58 && symbol <= 64)
		|| (symbol >= 91 && symbol <= 94 && symbol <= 96)
		|| (symbol >= 123 && symbol <= 126))
		return (1);
	return (0);
}

void    unset_valid_variable_name(char *var)
{
	int	b;

	b = 0;
	while (var[b] == '_')
		b++;
	while (var[b])
	{
		if (forchar(var[b]) == 1)
		{
			write(2, "syntax error near unexpected token\n", 35);
			return ;
		}
		b++;
	}
	b = 0;
	if (ft_isalpha(var[b]) == 0 && var[0] != '_')
	{
		write(2, "unset: not a valid identifier\n", 30);
		b++;
		return ;
	}
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
