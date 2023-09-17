/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:19:20 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/17 18:41:45 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset_errorchar(int symbol)
{
	if ((symbol >= 33 && symbol <= 47) || (symbol >= 58 && symbol <= 64)
		|| (symbol >= 91 && symbol <= 94) || (symbol == 96)
		|| (symbol >= 123 && symbol <= 126))
		return (1);
	return (0);
}

void	unset_valid_variable_name(char *var)
{
	int	b;

	b = 0;
	while (var[b])
	{
		if (unset_errorchar(var[b]) == 1)
		{
			write(2, "syntax error near unexpected token\n", 35);
			g_exit_code = 1;
			return ;
		}
		b++;
	}
	b = 0;
	if (ft_isalpha(var[b]) == 0 && var[0] != '_')
	{
		write(2, "unset: not a valid identifier\n", 30);
		g_exit_code = 1;
		b++;
		return ;
	}
}

void	unset(t_data *data, t_parse *pars)
{
	t_env	*lst;
	int		i;

	i = 0;
	while (pars->cmd[++i])
	{
		unset_valid_variable_name(pars->cmd[i]);
		lst = data->env_lst;
		while (lst)
		{
			if (lst && sravnim(lst->key, pars->cmd[i]) == 0)
			{
				free(lst->key);
				free(lst->val);
				lst->key = ft_strdup("\0");
				lst->val = ft_strdup("\0");
				g_exit_code = 0;
				break ;
			}
			lst = lst->next;
		}
	}
}
