/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:19:20 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/12 18:38:14 by valeriafedo      ###   ########.fr       */
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
int	delet(t_data *data, t_parse *pars, t_env *lst, int i)
{
	if (ft_strncmp(lst->key, pars->cmd[i],
		ft_strlen(pars->cmd[i])) == 0 && ft_strncmp(lst->key,
		pars->cmd[i], ft_strlen(lst->key)) == 0)
	{
		lst = lst->next;
		data->env_lst = lst;
		return (1);
	}
	return (0);
}

void	unset(t_data *data, t_parse *pars)
{
	t_env	*lst;
	int		i;
	t_env	*prev;

	i = 0;
	while (pars->cmd[++i])
	{
		unset_valid_variable_name(pars->cmd[i]);
		prev = NULL;
		lst = data->env_lst;
		while (lst->next)
		{
			if (prev == NULL)
				if (delet(data, pars, lst, i) == 1)
					break ;
			prev = lst;
			if (lst->next->next && sravnim(lst->next->key, pars->cmd[i]) == 0)
			{
				lst->next = lst->next->next;
				break ;
			}
			lst = lst->next;
		}
	}
}
